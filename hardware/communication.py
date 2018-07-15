from serial import Serial


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
    return self._send_command(Command.STATUS)


def play_pattern(pattern):
    """
    Play a light pattern
    :param pattern: The identifier of the pattern.
    :return: True if the pattern was started, false otherwise.
    """
    return _send_command(Command.PLAY, pattern)


def turn_off():
    """
    Turn off the current light
    :return:
    """
    return _send_command(Command.STOP)


def _send_command(command, parameter=0):
    """
    Send a command including the parameter to the arduino.
    :param command: The command to send. An integer.
    :param parameter: The parameter to send with the command.
    :return True when the arduino responded with OK. False otherwise.
    """

    # Open the serial connection
    _serial = Serial(
        "/dev/ttyUSB0",
        9600,
        timeout=1.0
    )

    _serial.write(bytes([command, parameter]))

    data = _serial.read()
    if len(data) == 0:
        success = False
    else:
        success = data[0] == Response.OK

    _serial.close()
    return success

