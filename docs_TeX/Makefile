SHELL=/bin/sh
THESIS=dokumentace

all:	
	pdflatex ${THESIS}.tex
	bibtex ${THESIS}
	bibtex ${THESIS}
	pdflatex ${THESIS}.tex
	pdflatex ${THESIS}.tex


clean:
	rm -rf *.aux *.lof *.log *.lot *.toc *.bbl *.blg *.dvi