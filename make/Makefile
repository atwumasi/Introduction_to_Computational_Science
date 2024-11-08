# Converting tex into pdf and combine the latter.

SOURCES = $(sort $(wildcard mypage?.tex))
OBJECTS = $(patsubst %.tex, %.pdf, $(SOURCES))

booklet.pdf : $(OBJECTS)
	pdftk $^ cat output $@

mypage%.pdf : mypage%.tex
	pdflatex $^

all : booklet.pdf $(OBJECTS) 

.PHONY : clean
clean :
	rm *.log *.out *.aux mypage?.pdf

.PHONY : cleanall
cleanall :
	rm *.log *.out *.aux *.pdf











