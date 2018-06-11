from functools import wraps
from flask import request

import settings


def validate_api_key(f):
    @wraps(f)
    def decorated_function(*args, **kargs):
        api_key = request.args.get('api-key')
        if api_key is None or api_key != settings.API_KEY:
            return 'Invalid Request', 400
        return f(*args, **kargs)

    return decorated_function
