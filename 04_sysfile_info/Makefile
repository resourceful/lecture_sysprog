texfile = 04-sysfile_info.tex
outdir=/tmp

all: ${texfile}
	pdflatex --shell-escape --output-directory ${outdir} $< 

clean:
	rm *.aux *.log *.nav *.out *.snm *.toc *.vrb

o: ${texfile}
	gv ${outdir}/$(basename $<).pdf  &

final: ${texfile}
	pdflatex --shell-escape --output-directory ${outdir} $< 
	pdflatex --shell-escape --output-directory ${outdir} $< 
	cp ${outdir}/$(basename $<).pdf .

