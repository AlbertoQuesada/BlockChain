###################################################################################################
#                                                                                                 #
#   OpenNN: Open Neural Networks Library                                                          #
#   www.opennn.net                                                                                #
#                                                                                                 #
#   O P E N N N   P R O J E C T                                                                   #
#                                                                                                 #
#   Roberto Lopez                                                                                 #
#   Artelnics - Making intelligent use of data                                                    #
#   robertolopez@artelnics.com                                                                    #
#                                                                                                 #
###################################################################################################

# CONFIGURATION

TEMPLATE = subdirs

CONFIG += ordered

CONFIG(release, debug|release) {
DEFINES += NDEBUG
}

SUBDIRS += opennn
#SUBDIRS += blank
#SUBDIRS += examples
#SUBDIRS += tests
