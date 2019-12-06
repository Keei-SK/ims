all:
	latex dokumentace.tex
	bibtex dokumentace
	latex dokumentace.tex
	latex dokumentace.tex
	dvips -t a4 dokumentace.dvi
	ps2pdf dokumentace.ps
	
	rm -r dokumentace.aux dokumentace.log dokumentace.toc dokumentace.synctex.gz
	chmod +x remove_excess.sh

clean:
	rm -r dokumentace.aux dokumentace.log dokumentace.toc dokumentace.synctex.gz
