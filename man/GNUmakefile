################################################################################

# ============================
# 一共有四种文档：
#
# PDF
# HTML
# DOS
# UNIX
#
# 主要是用 groff 命令生成
#
# *** 生成 PDF 文档和 HTML 文档失败。
#     master 分支上也无法生成。
#     应该是我本地的环境问题。
# ============================

.PHONY: clean


# PDF files to create
PDFDOCS = vlmcs.1.pdf vlmcsd.7.pdf vlmcsd.8.pdf vlmcsdmulti.1.pdf vlmcsd.ini.5.pdf vlmcsd-floppy.7.pdf

HTMLDOCS = $(PDFDOCS:.pdf=.html)
UNIXDOCS = $(PDFDOCS:.pdf=.unix.txt)
DOSDOCS = $(PDFDOCS:.pdf=.dos.txt)

%.pdf : %
	# For Mac:
	#groff -Tps -mandoc -c $< | pstopdf -i -o $@
	# For Others:
	groff -Tpdf -mandoc -c $< > $@

%.html : %
	groff -Thtml -mandoc -c $< > $@ 

%.unix.txt : %
	groff -P -c -Tascii -mandoc -c $< | col -bx > $@

%.dos.txt : %.unix.txt
#	unix2dos -n $< $@
#	sed -e 's/$$/\r/' $< > $@
	awk 'sub("$$", "\r")' $< > $@


pdfdocs : $(PDFDOCS)

dosdocs : $(DOSDOCS)

unixdocs : $(UNIXDOCS)

htmldocs : $(HTMLDOCS)


clean:
	rm -f $(PDFDOCS) $(DOSDOCS) $(UNIXDOCS) $(HTMLDOCS)

