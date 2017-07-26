#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include "PIDController.h"
#include "ThrottleController.h"
#include <math.h>

// for convenience
using json = nlohmann::json;

#ifndef DEBUG
#define DEBUG true
#endif

std::string hasData(std::string s);

void runWebSocket(Controller &steering_controller, Controller &throttle_controller);

int main(int argc, char *argv[]) {
  if (argc!=2) {
    std::cout << "Running in low speed mode" << std::endl;
    const double targetSpeed = 25.;

    PIDController steering_controller = PIDController(PIDController::Type::cte, 0.3, 0.0002, 10.);
    PIDController throttle_controller = PIDController(PIDController::Type::speed, 1., 0., 0., targetSpeed);

    runWebSocket(steering_controller, throttle_controller);

  } else if (std::string("fast") == argv[1]) {
    std::cout << "Running in high speed mode" << std::endl;
    const double maxSpeed = 55.;

    PIDController steering_controller = PIDController(PIDController::Type::cte, 0.4, 0.0004, 20.);
    ThrottleController throttle_controller = ThrottleController(1., maxSpeed);

    runWebSocket(steering_controller, throttle_controller);
  } else {
    std::cout << "Unknown arguments passed..." << std::endl;
    std::cout << "Run with 'fast' or without arguments" << std::endl;
  }
}

void runWebSocket(Controller &steering_controller, Controller &throttle_controller) {
  uWS::Hub h;

  h.onMessage([&steering_controller, &throttle_controller](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length,
                                                           uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(std::string(data).substr(0, length));
      if (s != "") {
        auto j = json::parse(s);
        std::string event = j[0].get<std::string>();
        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<std::string>());
          double speed = std::stod(j[1]["speed"].get<std::string>());
          double angle = std::stod(j[1]["steering_angle"].get<std::string>());

          steering_controller.update(cte, speed, angle);
          throttle_controller.update(cte, speed, angle);

          std::string msg;
          if (steering_controller.isReset() || throttle_controller.isReset()) {
            msg = "42[\"reset\",{}]";
          } else {
            double steer_value = steering_controller.getControl();
            double throttle_value = throttle_controller.getControl();

            // DEBUG
            if (DEBUG) std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;

            json msgJson;
            msgJson["steering_angle"] = steer_value;
            msgJson["throttle"] = throttle_value;
            msg = "42[\"steer\"," + msgJson.dump() + "]";
          }

          if (DEBUG) std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }
      } else {
        // Manual driving
        std::string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }
  });

  // We don't need this since we're not using HTTP but if it's removed the program
  // doesn't compile :-(
  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
    const std::string s = "<h1>Hello world!</h1>";
    if (req.getUrl().valueLength == 1) {
      res->end(s.data(), s.length());
    } else {
      // i guess this should be done more gracefully?
      res->end(nullptr, 0);
    }
  });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    if (DEBUG) std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
    h.run();
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
  }
}

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::string hasData(std::string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != std::string::npos) {
    return "";
  } else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}