

class Reqeust(object):
    """
    A class to easily parse amazon alexa requests.
    """
    def __init__(self, request_content):
        self._request_content = request_content

    def is_turn_on_request(self):
        intent_name = self._get_intent_name()
        return intent_name == "TurnOn"

    def is_turn_off_request(self):
        intent_name = self._get_intent_name()
        return intent_name == "TurnOff"

    def is_play_request(self):
        intent_name = self._get_intent_name()
        return intent_name == "Play"

    def get_show(self):

    def _get_intent_name(self):
        """
        Get the name of the intent of this request.
        :return: The name of the intent or none if it was not an intent request
        """
        if "request" in self._request_content:
            request_info = self._request_content["request"]
            if "intent" in request_info:
                intent_name = request_info["name"]
                return intent_name

        return None

