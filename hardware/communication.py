from serial import Serial

# Initialize the serial
_serial = Serial(
    "/dev/ttyUSB0",
    9600,
    timeout=1.0
)

class Command:
    """
    Command 0 is reserved and may not be used.
    """
    STATUS = 1  # type: int
    PLAY = 10  # type: int
    STOP = 20 # type: int


class Response:
    OK = 1  # type: int


class LightPattern:
    NORMAL = 0  # type: int


def check_connectivity(self):
    """
    Check if the Arduino is connected and working
    :return: True if the arduino is connected and running as expected.
    """
    self._send_command(Command.STATUS)
    return self._check_ok()


def play_pattern(pattern):
    """
    Play a light pattern
    :param pattern: The identifier of the pattern.
    :return: True if the pattern was started, false otherwise.
    """
    _send_command(Command.PLAY, pattern)
    return _check_ok()


def turn_off():
    """
    Turn off the current light
    :return:
    """
    _send_command(Command.STOP)
    return _check_ok()


def _send_command(command, parameter=0):
    """
    Send a command including the parameter to the arduino.
    :param command: The command to send. An integer.
    :param parameter: The parameter to send with the command.
    """
    _serial.write(bytes([command, parameter]))


def _check_ok():
    """
    Check if the Arduino responded with an OK.
    :return:
    """
    data = _serial.read()
    if len(data) != 0:
        return False
    return data[0] == Response.OK
