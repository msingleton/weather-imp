// http://impurl?weather=(rain=0|snow=1)
server.log("Imp URL: " + http.agenturl());

function requestHandler(req, resp) {
  try {
    if (("weather" in req.query) && ("intensity" in req.query)) {
        device.send("weather", req.query.weather + "&" + req.query.intensity);
    }

    resp.send(200, "OK");
  } catch (e) {
    resp.send(500, "Error: " + e);
  }
}

http.onrequest(requestHandler);