rem ---------------------------
rem Transformaci¢n de CEL a INC
rem por Fernando Gonzalez Ruano
rem       (Fegor) - 1.996
rem ---------------------------

celtospr p1
celtospr p2
celtospr p3
celtospr bomban
celtospr bombae
celtospr bombas
celtospr bombao
celtospr t1n1m
celtospr t1e1m
celtospr t1s1m
celtospr t1o1m
celtospr t1n2m
celtospr t1e2m
celtospr t1s2m
celtospr t1o2m
celtospr t2n1m
celtospr t2e1m
celtospr t2s1m
celtospr t2o1m
celtospr t2n2m
celtospr t2e2m
celtospr t2s2m
celtospr t2o2m
celtospr cruzroja
celtospr municion
celtospr fuel
celtospr destrozo
celtospr ladrillo
celtospr basev
celtospr basea
celtospr foto

copy p1.spr+p2.spr+p3.spr+bomban.spr+bombae.spr+bombas.spr+bombao.spr /b sprt1~ /b
copy t1n1m.spr+t1e1m.spr+t1s1m.spr+t1o1m.spr+t1n2m.spr+t1e2m.spr+t1s2m.spr+t1o2m.spr /b sprt2~ /b
copy t2n1m.spr+t2e1m.spr+t2s1m.spr+t2o1m.spr+t2n2m.spr+t2e2m.spr+t2s2m.spr+t2o2m.spr /b sprt3~ /b
copy cruzroja.spr+municion.spr+fuel.spr+destrozo.spr+ladrillo.spr+basev.spr+basea.spr /b sprt4~ /b
copy foto.spr /b sprt5~

del *.spr

copy sprt1~+sprt2~+sprt3~+sprt4~+sprt5~ /b tanques.spr /b

del sprt?~

celtopal t1n1m

copy tanques.spr ..
copy tanques.pal ..
del  tanques.spr
del  tanques.pal

