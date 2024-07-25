# Universal makefile for single C++ program
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependencies among source files.
# Use make default rules for commonly used file-name suffixes and make variables names.
#
# % make [ a.out ]

########## Variables ##########

CXX = g++-11					# compiler
CXXFLAGS = -std=c++20 -g -Wall -Werror=vla -MMD -Iincludes			# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

SOURCES = position.cc move.cc piece.cc knight.cc bishop.cc pawn.cc rook.cc queen.cc king.cc observer.cc textview.cc windowview.cc window.cc subject.cc board.cc controller.cc	main.cc		# source files (*.cc)
OBJECTS = ${SOURCES:.cc=.o}			# object files forming executable
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXEC = chess					# executable name

########## Targets ##########

.PHONY : clean					# not file names

${EXEC} : ${OBJECTS}				# link step
	${CXX} ${CXXFLAGS} $^ -o $@ -lX11		# additional object files before $^

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

# make implicitly generates rules to compile C++ files that generate .o files

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}