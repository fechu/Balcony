from flask import Flask
from actions.led import led_page

# Setup the app!
app = Flask(__name__)
app.register_blueprint(led_page, url_prefix='/led')


if __name__ == '__main__':
    app.run(
        host='0.0.0.0',
        port=2222,
        ssl_context=(
            '/etc/letsencrypt/live/www.wg-pi.changeip.net/fullchain.pem',
            '/etc/letsencrypt/live/www.wg-pi.changeip.net/privkey.pem'
        ))
