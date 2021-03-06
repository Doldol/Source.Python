# ../settings/menu.py

"""Registers client/say commands used to send the main user settings menu."""

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Menus
from menus import PagedMenu
#   Players
from players.helpers import index_from_playerinfo
#   Settings
from settings import _settings_strings


# =============================================================================
# >> FUNCTIONS
# =============================================================================
class _AvailableSettings(dict):

    """Holds all settings.player.PlayerSettings instance menus."""

    def __init__(self):
        """Create the main settings menu on instantiation."""
        super(_AvailableSettings, self).__init__()
        self._menu = PagedMenu(
            select_callback=self._chosen_item,
            title=_settings_strings['Main Title'])

    @property
    def menu(self):
        """Return the main settings menu instance."""
        return self._menu

    def _private_send_menu(self, *args):
        """Called when a private say command is used for sending the menu."""
        # Send the menu
        self._send_menu(*args)

        # Make the command private
        return False

    def _send_menu(self, playerinfo, *args):
        """Send the main settings menu to the player who requested it."""
        self.menu.send(index_from_playerinfo(playerinfo))

    @staticmethod
    def _chosen_item(menu, index, option):
        """Send a PlayerSettings menu when one is chosen from the main menu."""
        option.value.menu.send(index)

# Get the _AvailableSettings instance
_player_settings = _AvailableSettings()
