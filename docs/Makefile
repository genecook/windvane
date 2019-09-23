ASCIIDOC := asciidoc

MY_DOCS := index.html a64sim_features.html a64sim_quick_start.html \
           a64sim_command_line.html a64sim_configuration.html \
           a64sim_links.html a64sim_license.html a64sim_brochure.html

all: logo.png ${MY_DOCS}

logo.png:
	cp ../simtrace_viewer/images/logo.png .

index.html: index.txt
	${ASCIIDOC} index.txt

a64sim_features.html: a64sim_features.txt
	${ASCIIDOC} a64sim_features.txt

a64sim_quick_start.html: a64sim_quick_start.txt
	${ASCIIDOC} a64sim_quick_start.txt

a64sim_command_line.html: a64sim_command_line.txt
	${ASCIIDOC} a64sim_command_line.txt

a64sim_configuration.html: a64sim_configuration.txt
	${ASCIIDOC} a64sim_configuration.txt

a64sim_links.html: a64sim_links.txt
	${ASCIIDOC} a64sim_links.txt

a64sim_license.html: a64sim_license.txt
	${ASCIIDOC} a64sim_license.txt

a64sim_brochure.html: a64sim_brochure.txt
	${ASCIIDOC} a64sim_brochure.txt


clean:
	rm -f ${MY_DOCS}
