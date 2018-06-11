from flask import Blueprint, request, jsonify
from decorators import validate_api_key

led_page = Blueprint('led_page', __name__)


@led_page.route('/on', methods=['POST', 'GET'])
@validate_api_key
def turn_on():
    response = {
        "version": "1.0",
        "response": {
            "outputSpeech": {
                "type": "PlainText",
                "text": "Today will provide you a new learning opportunity.  Stick with it and the possibilities will be endless. Can I help you with anything else?"
            },
            "card": {
                "type": "Simple",
                "title": "Horoscope",
                "content": "Today will provide you a new learning opportunity.  Stick with it and the possibilities will be endless."
            },
            "reprompt": {
                "outputSpeech": {
                    "type": "PlainText",
                    "text": "Can I help you with anything else?"
                }
            },
            "shouldEndSession": False
        }
    }
    return jsonify(response)