# ../messages/__init__.py

"""Provides user message based functionality."""

# ============================================================================
# >> IMPORTS
# ============================================================================
# Source.Python Imports
#   Core
from core import GAME_NAME
#   Loggers
from loggers import _sp_logger
#   Messages
from messages.base import _UserMessages
#   Paths
from paths import SP_DATA_PATH


# ============================================================================
# >> FORWARD IMPORTS
# ============================================================================
#   Messages
from _messages import DialogType


# =============================================================================
# >> ALL DECLARATION
# =============================================================================
__all__ = ('DialogType',
           )


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the sp.messages logger
messages_logger = _sp_logger.messages


# ============================================================================
# >> INITIALIZATION
# ============================================================================
# Loop trough all message classes
for message_name, message_class in _UserMessages(SP_DATA_PATH.joinpath(
    'messages', 'usermessages.ini'), SP_DATA_PATH.joinpath(
        'messages', 'games', GAME_NAME + '.ini')).items():

    # Globalize the current message class
    globals()[message_name] = message_class

    # Add the object, by name, to __all__
    __all__ = tuple(sorted(list(__all__) + [message_name]))
