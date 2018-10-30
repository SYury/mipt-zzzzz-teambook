build : texify compile clean

texify :
	python3 texify.py

compile :
	pdflatex -shell-escape teambook.tex
	pdflatex -shell-escape teambook.tex

clean :
	rm -f teambook.{aux,log,toc}
	rm -rf _minted-teambook
	rm teambook.tex
