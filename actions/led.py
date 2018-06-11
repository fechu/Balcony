from flask import Blueprint, request
from decorators import validate_api_key

led_page = Blueprint('led_page', __name__)


@led_page.route('/on')
@validate_api_key
def turn_on():
    return "success", 200