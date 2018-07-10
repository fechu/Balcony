

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
        return intent_name == "TurnOff" or intent_name == "AMAZON.StopIntent"

    def is_play_request(self):
        intent_name = self._get_intent_name()
        return intent_name == "Play"

    def get_show(self):
        """
        Get the id of the show slot.
        :return: The name of the show on success, None otherwise.
        """

        keys = [
            "request",
            "intent",
            "slots",
            "show",
            "resolutions",
            "resolutionsPerAuthority"
        ]

        current_dir = self._request_content
        for key in keys:
            if key not in current_dir:
                break
            current_dir = current_dir[key]

        # resolutionsPerAuthority is an array
        if len(current_dir) > 0:
            current_dir = current_dir[0]
            if "values" in current_dir and len(current_dir["values"]) > 0:
                current_dir = current_dir["values"][0]
                if "value" in current_dir and "id" in current_dir["value"]:
                    return int(current_dir["value"]["id"])

        return None

    def _get_intent_name(self):
        """
        Get the name of the intent of this request.
        :return: The name of the intent or none if it was not an intent request
        """
        if "request" in self._request_content:
            request_info = self._request_content["request"]
            if "intent" in request_info:
                intent_name = request_info["intent"]["name"]
                return intent_name

        return None

