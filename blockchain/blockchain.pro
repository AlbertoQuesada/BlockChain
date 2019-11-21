###################################################################################################
#                                                                                                 #
#   P E R S O N A L   P R O J E C T                                                               #
#                                                                                                 #
#   Alberto Quesada                                                                               #
#                                                                                                 #
###################################################################################################

# CONFIGURATION

TEMPLATE = subdirs

CONFIG += ordered

CONFIG(release, debug|release) {
DEFINES += NDEBUG
}

SUBDIRS += opennn
SUBDIRS += projects
  