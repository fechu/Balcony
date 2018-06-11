from flask import Flask

app = Flask(__name__)


@app.route("/")
def hello():
    return "Hello World"

if __name__ == '__main__':
    app.run(
        host='0.0.0.0',
        port=2222,
        ssl_context=(
            '/etc/letsencrypt/live/www.wg-pi.changeip.net/fullchain.pem',
            '/etc/letsencrypt/live/www.wg-pi.changeip.net/privkey.pem'
        ))
