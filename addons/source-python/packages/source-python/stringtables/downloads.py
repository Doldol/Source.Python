# ../stringtables/downloads.py

"""Provides access to the Downloadables stringtable."""

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import AutoUnload
#   Events
from events.manager import event_manager
#   Stringtables
from stringtables import string_tables


# =============================================================================
# >> ALL DECLARATION
# =============================================================================
__all__ = ('Downloadables',
           )


# =============================================================================
# >> CLASSES
# =============================================================================
class Downloadables(AutoUnload, set):

    """Class used to store downloadables for a script."""

    def __init__(self):
        """Add the instance to the downloadables list."""
        super(Downloadables, self).__init__()
        _downloadables_list.append(self)

    def add(self, item):
        """Add an item to the downloadables for a script."""
        # Is the item already in the list?
        if item in self:

            # If so, no need to add it
            return

        # Add the item to the downloadables stringtable
        _downloadables_list._add_to_download_table(item)

        # Add the item to the script's downloadables
        super(Downloadables, self).add(item)

    def _set_all_downloads(self):
        """Add all downloadables for the script on level init."""
        # Loop through all items in the list
        for item in self:

            # Add the item to the downloadables stringtable
            _downloadables_list._add_to_download_table(item)

    def _unload_instance(self):
        """Remove the instance from the downloadables list."""
        _downloadables_list.remove(self)


class _DownloadablesList(list):

    """List object used to store downloads on a per-script basis."""

    def __init__(self):
        """Refresh the downloadables table instance."""
        super(_DownloadablesList, self).__init__()
        self._refresh_table_instance()

    def _refresh_table_instance(self):
        """Get the current instance of the downloadables table."""
        self.download_table = string_tables.downloadables

    def _add_to_download_table(self, item):
        """Add the given file to the downloadables table."""
        # Is the server still in launching process?
        if self.download_table is None:

            # If so, no need to go further...
            return

        # Add the given file to the downloadables table.
        self.download_table.add_string(item, item)

    def server_spawn(self, game_event):
        """Add all items stored as downloadables to the stringtable."""
        # Refresh the downloadables table instance
        self._refresh_table_instance()

        # Loop through all items in the list
        for item in self:

            # Set all items in the current item as downloadables
            item._set_all_downloads()

# Get the _DownloadablesList instance
_downloadables_list = _DownloadablesList()

# Register for the event server_spawn in
# order to reset all downloads on map change
event_manager.register_for_event(
    'server_spawn', _downloadables_list.server_spawn)
