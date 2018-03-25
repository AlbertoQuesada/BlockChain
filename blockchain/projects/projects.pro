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

#SUBDIRS += solidus_desk
SUBDIRS += property_finder
#SUBDIRS += lurmetrika
#SUBDIRS += acciona_agua
SUBDIRS += seat_fast_lane
SUBDIRS += block_chain
#SUBDIRS += platinium
