import alexa
import json
from flask import Blueprint, request, jsonify
from decorators import validate_api_key
from hardware import communication

led_page = Blueprint('led_page', __name__)


@led_page.route('/', methods=['POST', 'GET'])
@validate_api_key
def turn_on():

    print(json.dumps(request.json, indent=2))
    alexa_request = alexa.Reqeust(request.json)

    if alexa_request.is_play_request():
        pattern_id = alexa_request.get_show()
        text = "Of course!"
        communication.play_pattern(pattern_id)
        # TODO: Implement mapping from name to name/id to pattern
    elif alexa_request.is_turn_on_request():
        text = "Turning on lights."
        communication.play_pattern(communication.LightPattern.NORMAL)
    elif alexa_request.is_turn_off_request():
        text = "Turning off lights."
        communication.turn_off()
    else:
        text = "Unknown intent..."

    response = {
        "version": "1.0",
        "response": {
            "outputSpeech": {
                "type": "PlainText",
                "text": text
            },
            "shouldEndSession": True
        }
    }
    return jsonify(response)