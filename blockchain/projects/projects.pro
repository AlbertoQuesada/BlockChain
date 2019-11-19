###################################################################################################
#                                                                                                 #
#   OpenNN: Open Neural Networks Library                                                          #
#   www.opennn.net                                                                                #
#                                                                                                 #
#   P R O J E C T S                                                                               #
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

SUBDIRS += block_chain
