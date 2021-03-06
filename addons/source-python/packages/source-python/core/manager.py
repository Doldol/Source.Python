# ../core/manager.py

"""Provides access to all plugins loaded via "sp load"."""

# =============================================================================
# >> IMPORTS
# =============================================================================
# Source.Python Imports
#   Core
from core import core_logger
#   Plugins
from plugins.manager import PluginManager


# =============================================================================
# >> ALL DECLARATION
# =============================================================================
__all__ = ('core_plugin_manager',
           )


# =============================================================================
# >> GLOBAL VARIABLES
# =============================================================================
# Get the sp.core.manager logger
core_manager_logger = core_logger.manager


# =============================================================================
# >> CLASSES
# =============================================================================
class _CorePluginManager(PluginManager):

    """Plugin Manager class used to load "sp" plugins."""

    logger = core_manager_logger

# Get the _CorePluginManager instance
core_plugin_manager = _CorePluginManager()
