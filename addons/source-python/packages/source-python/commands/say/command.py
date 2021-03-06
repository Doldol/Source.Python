# ../commands/say/command.py

"""Provides a decorator class for registering say commands."""

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Commands
from commands.command import _BaseCommand
from commands.say.manager import say_command_manager


# =============================================================================
# >> CLASSES
# =============================================================================
class SayCommand(_BaseCommand):

    """Decorator class used to register a say command."""

    # Store the class used to (un)register say commands
    _manager_class = say_command_manager
