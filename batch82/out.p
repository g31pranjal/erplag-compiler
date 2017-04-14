
[1m[32mInput source code has no syntactical errors.[0m

readArr		4		ID		---		<moduleDeclarations> (1cd7f40)		YES		---
<program> ( 1cd7e60 ) parent of <moduleDeclarations> ( 1cd7f40 )
---		---		---		---		ROOT		NO		<program>
arraySum		5		ID		---		<module> (1cd86b0)		YES		---
<otherModules> ( 1cd7fb0 ) parent of <module> ( 1cd86b0 )
list		6		ID		---		<input_plist> (1cd8ae0)		YES		---
<module> ( 1cd86b0 ) parent of <input_plist> ( 1cd8ae0 )
array		6		ARRAY		---		<dataType> (1cd91a0)		YES		---
<input_plist> ( 1cd8ae0 ) parent of <dataType> ( 1cd91a0 )
1		6		NUM		1		<range> (1cd9480)		YES		---
<dataType> ( 1cd91a0 ) parent of <range> ( 1cd9480 )
15		6		NUM		15		<range> (1cd9480)		YES		---
real		6		REAL		---		<dataType> (1cd91a0)		YES		---
n		6		ID		---		<input_plist> (1cd8ae0)		YES		---
integer		6		INTEGER		---		<dataType> (1cd9d10)		YES		---
<input_plist> ( 1cd8ae0 ) parent of <dataType> ( 1cd9d10 )
sum		7		ID		---		<output_plist> (1cda300)		YES		---
<module> ( 1cd86b0 ) parent of <output_plist> ( 1cda300 )
real		7		REAL		---		<output_plist> (1cda300)		YES		---
start		8		START		---		<moduleDef> (1cd8ca0)		YES		---
<module> ( 1cd86b0 ) parent of <moduleDef> ( 1cd8ca0 )
index		9		ID		---		<idList> (1cdaea0)		YES		---
<declareStmt> ( 1cdada0 ) parent of <idList> ( 1cdaea0 )
<statements> ( 1cdaaf0 ) parent of <declareStmt> ( 1cdada0 )
integer		9		INTEGER		---		<dataType> (1cdaf80)		YES		---
<declareStmt> ( 1cdada0 ) parent of <dataType> ( 1cdaf80 )
<moduleDef> ( 1cd8ca0 ) parent of <statements> ( 1cdaaf0 )
t		10		ID		---		<idList> (1cdb780)		YES		---
<declareStmt> ( 1cdb680 ) parent of <idList> ( 1cdb780 )
a		10		ID		---		<idList> (1cdb780)		YES		---
<statements> ( 1cdaaf0 ) parent of <declareStmt> ( 1cdb680 )
boolean		10		BOOLEAN		---		<dataType> (1cdb860)		YES		---
<declareStmt> ( 1cdb680 ) parent of <dataType> ( 1cdb860 )
sum		11		ID		---		<assignmentStmt> (1cdc240)		YES		---
<simpleStmt> ( 1cdc1b0 ) parent of <assignmentStmt> ( 1cdc240 )
:=		11		ASSIGNOP		---		<assignmentStmt> (1cdc240)		YES		---
0.0		11		RNUM		0.0		<var> (1cdcbe0)		YES		---
<expression> ( 1cdc420 ) parent of <var> ( 1cdcbe0 )
<assignmentStmt> ( 1cdc240 ) parent of <expression> ( 1cdc420 )
<statements> ( 1cdaaf0 ) parent of <simpleStmt> ( 1cdc1b0 )
t		12		ID		---		<assignmentStmt> (1cdd190)		YES		---
<simpleStmt> ( 1cdd100 ) parent of <assignmentStmt> ( 1cdd190 )
:=		12		ASSIGNOP		---		<assignmentStmt> (1cdd190)		YES		---
true		12		TRUE		---		<var> (1cddb30)		YES		---
<expression> ( 1cdd370 ) parent of <var> ( 1cddb30 )
<assignmentStmt> ( 1cdd190 ) parent of <expression> ( 1cdd370 )
<statements> ( 1cdaaf0 ) parent of <simpleStmt> ( 1cdd100 )
while		13		WHILE		---		<iterativeStmt> (1cde050)		YES		---
<statements> ( 1cdaaf0 ) parent of <iterativeStmt> ( 1cde050 )
sum		13		ID		---		<var> (1cde9f0)		YES		---
GE ( 1cde570 ) parent of <var> ( 1cde9f0 )
AND ( 1cde1c0 ) parent of GE ( 1cde570 )
12.8		13		RNUM		12.8		<var> (1cdf270)		YES		---
GE ( 1cde570 ) parent of <var> ( 1cdf270 )
<iterativeStmt> ( 1cde050 ) parent of AND ( 1cde1c0 )
t		13		ID		---		<var> (1cdfb80)		YES		---
AND ( 1cde1c0 ) parent of <var> ( 1cdfb80 )
start		14		START		---		<iterativeStmt> (1cde050)		YES		---
p		15		ID		---		<idList> (1ce0310)		YES		---
<declareStmt> ( 1ce0210 ) parent of <idList> ( 1ce0310 )
q		15		ID		---		<idList> (1ce0310)		YES		---
r		15		ID		---		<idList> (1ce0310)		YES		---
<statements> ( 1cde310 ) parent of <declareStmt> ( 1ce0210 )
array		15		ARRAY		---		<dataType> (1ce03f0)		YES		---
<declareStmt> ( 1ce0210 ) parent of <dataType> ( 1ce03f0 )
1		15		NUM		1		<range> (1ce0d90)		YES		---
<dataType> ( 1ce03f0 ) parent of <range> ( 1ce0d90 )
12		15		NUM		12		<range> (1ce0d90)		YES		---
boolean		15		BOOLEAN		---		<dataType> (1ce03f0)		YES		---
<iterativeStmt> ( 1cde050 ) parent of <statements> ( 1cde310 )
newarr		16		ID		---		<idList> (1ce1740)		YES		---
<declareStmt> ( 1ce1640 ) parent of <idList> ( 1ce1740 )
<statements> ( 1cde310 ) parent of <declareStmt> ( 1ce1640 )
array		16		ARRAY		---		<dataType> (1ce1820)		YES		---
<declareStmt> ( 1ce1640 ) parent of <dataType> ( 1ce1820 )
1		16		NUM		1		<range> (1ce1d20)		YES		---
<dataType> ( 1ce1820 ) parent of <range> ( 1ce1d20 )
15		16		NUM		15		<range> (1ce1d20)		YES		---
real		16		REAL		---		<dataType> (1ce1820)		YES		---
u		17		ID		---		<idList> (1ce26d0)		YES		---
<declareStmt> ( 1ce25d0 ) parent of <idList> ( 1ce26d0 )
v		17		ID		---		<idList> (1ce26d0)		YES		---
<statements> ( 1cde310 ) parent of <declareStmt> ( 1ce25d0 )
boolean		17		BOOLEAN		---		<dataType> (1ce27b0)		YES		---
<declareStmt> ( 1ce25d0 ) parent of <dataType> ( 1ce27b0 )
while		18		WHILE		---		<iterativeStmt> (1ce3100)		YES		---
<statements> ( 1cde310 ) parent of <iterativeStmt> ( 1ce3100 )
sum		18		ID		---		<var> (1ce3aa0)		YES		---
MINUS ( 1ce3740 ) parent of <var> ( 1ce3aa0 )
OR ( 1ce3270 ) parent of MINUS ( 1ce3740 )
3.0		18		RNUM		3.0		<var> (1ce4170)		YES		---
MINUS ( 1ce3740 ) parent of <var> ( 1ce4170 )
<iterativeStmt> ( 1ce3100 ) parent of OR ( 1ce3270 )
sum		18		ID		---		<var> (1ce4a80)		YES		---
LE ( 1ce4500 ) parent of <var> ( 1ce4a80 )
OR ( 1ce3270 ) parent of LE ( 1ce4500 )
20.3		18		RNUM		20.3		<var> (1ce5300)		YES		---
LE ( 1ce4500 ) parent of <var> ( 1ce5300 )
start		19		START		---		<iterativeStmt> (1ce3100)		YES		---
x		20		ID		---		<idList> (1ce5970)		YES		---
<declareStmt> ( 1ce5870 ) parent of <idList> ( 1ce5970 )
y		20		ID		---		<idList> (1ce5970)		YES		---
<statements> ( 1ce33c0 ) parent of <declareStmt> ( 1ce5870 )
integer		20		INTEGER		---		<dataType> (1ce5a50)		YES		---
<declareStmt> ( 1ce5870 ) parent of <dataType> ( 1ce5a50 )
<iterativeStmt> ( 1ce3100 ) parent of <statements> ( 1ce33c0 )
x		21		ID		---		<assignmentStmt> (1ce6430)		YES		---
<simpleStmt> ( 1ce63a0 ) parent of <assignmentStmt> ( 1ce6430 )
:=		21		ASSIGNOP		---		<assignmentStmt> (1ce6430)		YES		---
y		21		ID		---		<var> (1ce6dd0)		YES		---
PLUS ( 1ce6a70 ) parent of <var> ( 1ce6dd0 )
<expression> ( 1ce6610 ) parent of PLUS ( 1ce6a70 )
3		21		NUM		3		<var> (1ce74a0)		YES		---
MUL ( 1ce7160 ) parent of <var> ( 1ce74a0 )
MINUS ( 1ce6c00 ) parent of MUL ( 1ce7160 )
index		21		ID		---		<var> (1ce78a0)		YES		---
MUL ( 1ce7160 ) parent of <var> ( 1ce78a0 )
PLUS ( 1ce6a70 ) parent of MINUS ( 1ce6c00 )
32		21		NUM		32		<var> (1ce7f70)		YES		---
MUL ( 1ce7c30 ) parent of <var> ( 1ce7f70 )
MINUS ( 1ce6c00 ) parent of MUL ( 1ce7c30 )
5		21		NUM		5		<var> (1ce8370)		YES		---
MUL ( 1ce7c30 ) parent of <var> ( 1ce8370 )
<assignmentStmt> ( 1ce6430 ) parent of <expression> ( 1ce6610 )
<statements> ( 1ce33c0 ) parent of <simpleStmt> ( 1ce63a0 )
sum		22		ID		---		<assignmentStmt> (1ce8920)		YES		---
<simpleStmt> ( 1ce8890 ) parent of <assignmentStmt> ( 1ce8920 )
:=		22		ASSIGNOP		---		<assignmentStmt> (1ce8920)		YES		---
p		22		ID		---		<var> (1ce92c0)		YES		---
PLUS ( 1ce8f60 ) parent of <var> ( 1ce92c0 )
<expression> ( 1ce8b00 ) parent of PLUS ( 1ce8f60 )
23.5		22		RNUM		23.5		<var> (1ce9990)		YES		---
PLUS ( 1ce8f60 ) parent of <var> ( 1ce9990 )
<assignmentStmt> ( 1ce8920 ) parent of <expression> ( 1ce8b00 )
<statements> ( 1ce33c0 ) parent of <simpleStmt> ( 1ce8890 )
t		23		ID		---		<assignmentStmt> (1ce9f40)		YES		---
<simpleStmt> ( 1ce9eb0 ) parent of <assignmentStmt> ( 1ce9f40 )
:=		23		ASSIGNOP		---		<assignmentStmt> (1ce9f40)		YES		---
true		23		TRUE		---		<var> (1cea8e0)		YES		---
OR ( 1cea3d0 ) parent of <var> ( 1cea8e0 )
<expression> ( 1cea120 ) parent of OR ( 1cea3d0 )
y		23		ID		---		<var> (1ceb1f0)		YES		---
PLUS ( 1ceae90 ) parent of <var> ( 1ceb1f0 )
GE ( 1ceac70 ) parent of PLUS ( 1ceae90 )
23		23		NUM		23		<var> (1ceb8c0)		YES		---
PLUS ( 1ceae90 ) parent of <var> ( 1ceb8c0 )
AND ( 1cea4d0 ) parent of GE ( 1ceac70 )
x		23		ID		---		<var> (1cec020)		YES		---
GE ( 1ceac70 ) parent of <var> ( 1cec020 )
OR ( 1cea3d0 ) parent of AND ( 1cea4d0 )
23.5		23		RNUM		23.5		<var> (1ceca50)		YES		---
LE ( 1cec4d0 ) parent of <var> ( 1ceca50 )
AND ( 1cea4d0 ) parent of LE ( 1cec4d0 )
newarr		23		ID		---		<var> (1ced1b0)		YES		---
LE ( 1cec4d0 ) parent of <var> ( 1ced1b0 )
10		23		NUM		10		<index> (1ced420)		YES		---
<var> ( 1ced1b0 ) parent of <index> ( 1ced420 )
<assignmentStmt> ( 1ce9f40 ) parent of <expression> ( 1cea120 )
<statements> ( 1ce33c0 ) parent of <simpleStmt> ( 1ce9eb0 )
end		24		END		---		<iterativeStmt> (1ce3100)		YES		---
index		25		ID		---		<assignmentStmt> (1cedc00)		YES		---
<simpleStmt> ( 1cedb70 ) parent of <assignmentStmt> ( 1cedc00 )
:=		25		ASSIGNOP		---		<assignmentStmt> (1cedc00)		YES		---
34		25		NUM		34		<var> (1cee5a0)		YES		---
MINUS ( 1cee240 ) parent of <var> ( 1cee5a0 )
<expression> ( 1cedde0 ) parent of MINUS ( 1cee240 )
20		25		NUM		20		<var> (1ceeb50)		YES		---
MUL ( 1cee810 ) parent of <var> ( 1ceeb50 )
PLUS ( 1cee3d0 ) parent of MUL ( 1cee810 )
index		25		ID		---		<var> (1ceef50)		YES		---
MUL ( 1cee810 ) parent of <var> ( 1ceef50 )
MINUS ( 1cee240 ) parent of PLUS ( 1cee3d0 )
x		25		ID		---		<var> (1cef620)		YES		---
MINUS ( 1cee880 ) parent of <var> ( 1cef620 )
PLUS ( 1cee3d0 ) parent of MINUS ( 1cee880 )
12		25		NUM		12		<var> (1cefcf0)		YES		---
MINUS ( 1cee880 ) parent of <var> ( 1cefcf0 )
<assignmentStmt> ( 1cedc00 ) parent of <expression> ( 1cedde0 )
<statements> ( 1cde310 ) parent of <simpleStmt> ( 1cedb70 )
r		26		ID		---		<assignmentStmt> (1cf02a0)		YES		---
<simpleStmt> ( 1cf0210 ) parent of <assignmentStmt> ( 1cf02a0 )
2		26		NUM		2		<index> (1cf06c0)		YES		---
<assignmentStmt> ( 1cf02a0 ) parent of <index> ( 1cf06c0 )
:=		26		ASSIGNOP		---		<assignmentStmt> (1cf02a0)		YES		---
p		26		ID		---		<var> (1cf0ee0)		YES		---
PLUS ( 1cf0b80 ) parent of <var> ( 1cf0ee0 )
3		26		NUM		3		<index> (1cf1150)		YES		---
<var> ( 1cf0ee0 ) parent of <index> ( 1cf1150 )
<expression> ( 1cf0480 ) parent of PLUS ( 1cf0b80 )
q		26		ID		---		<var> (1cf1850)		YES		---
PLUS ( 1cf0b80 ) parent of <var> ( 1cf1850 )
4		26		NUM		4		<index> (1cf1ac0)		YES		---
<var> ( 1cf1850 ) parent of <index> ( 1cf1ac0 )
<assignmentStmt> ( 1cf02a0 ) parent of <expression> ( 1cf0480 )
<statements> ( 1cde310 ) parent of <simpleStmt> ( 1cf0210 )
r		27		ID		---		<assignmentStmt> (1cf21c0)		YES		---
<simpleStmt> ( 1cf2130 ) parent of <assignmentStmt> ( 1cf21c0 )
3		27		NUM		3		<index> (1cf25e0)		YES		---
<assignmentStmt> ( 1cf21c0 ) parent of <index> ( 1cf25e0 )
:=		27		ASSIGNOP		---		<assignmentStmt> (1cf21c0)		YES		---
p		27		ID		---		<var> (1cf2e00)		YES		---
PLUS ( 1cf2aa0 ) parent of <var> ( 1cf2e00 )
1		27		NUM		1		<index> (1cf3070)		YES		---
<var> ( 1cf2e00 ) parent of <index> ( 1cf3070 )
<expression> ( 1cf23a0 ) parent of PLUS ( 1cf2aa0 )
list		27		ID		---		<var> (1cf3770)		YES		---
PLUS ( 1cf2aa0 ) parent of <var> ( 1cf3770 )
2		27		NUM		2		<index> (1cf39e0)		YES		---
<var> ( 1cf3770 ) parent of <index> ( 1cf39e0 )
<assignmentStmt> ( 1cf21c0 ) parent of <expression> ( 1cf23a0 )
<statements> ( 1cde310 ) parent of <simpleStmt> ( 1cf2130 )
newarr		28		ID		---		<assignmentStmt> (1cf40e0)		YES		---
<simpleStmt> ( 1cf4050 ) parent of <assignmentStmt> ( 1cf40e0 )
12		28		NUM		12		<index> (1cf4500)		YES		---
<assignmentStmt> ( 1cf40e0 ) parent of <index> ( 1cf4500 )
:=		28		ASSIGNOP		---		<assignmentStmt> (1cf40e0)		YES		---
list		28		ID		---		<var> (1cf4d20)		YES		---
PLUS ( 1cf49c0 ) parent of <var> ( 1cf4d20 )
10		28		NUM		10		<index> (1cf4f90)		YES		---
<var> ( 1cf4d20 ) parent of <index> ( 1cf4f90 )
<expression> ( 1cf42c0 ) parent of PLUS ( 1cf49c0 )
list		28		ID		---		<var> (1cf5690)		YES		---
PLUS ( 1cf49c0 ) parent of <var> ( 1cf5690 )
5		28		NUM		5		<index> (1cf5900)		YES		---
<var> ( 1cf5690 ) parent of <index> ( 1cf5900 )
<assignmentStmt> ( 1cf40e0 ) parent of <expression> ( 1cf42c0 )
<statements> ( 1cde310 ) parent of <simpleStmt> ( 1cf4050 )
t		29		ID		---		<assignmentStmt> (1cf6000)		YES		---
<simpleStmt> ( 1cf5f70 ) parent of <assignmentStmt> ( 1cf6000 )
:=		29		ASSIGNOP		---		<assignmentStmt> (1cf6000)		YES		---
list		29		ID		---		<var> (1cf72b0)		YES		---
PLUS ( 1cf6f50 ) parent of <var> ( 1cf72b0 )
10		29		NUM		10		<index> (1cf7520)		YES		---
<var> ( 1cf72b0 ) parent of <index> ( 1cf7520 )
LE ( 1cf6d30 ) parent of PLUS ( 1cf6f50 )
34.5		29		RNUM		34.5		<var> (1cf7c20)		YES		---
PLUS ( 1cf6f50 ) parent of <var> ( 1cf7c20 )
AND ( 1cf6490 ) parent of LE ( 1cf6d30 )
newarr		29		ID		---		<var> (1cf8380)		YES		---
LE ( 1cf6d30 ) parent of <var> ( 1cf8380 )
1		29		NUM		1		<index> (1cf85f0)		YES		---
<var> ( 1cf8380 ) parent of <index> ( 1cf85f0 )
<expression> ( 1cf61e0 ) parent of AND ( 1cf6490 )
<assignmentStmt> ( 1cf6000 ) parent of <expression> ( 1cf61e0 )
<statements> ( 1cde310 ) parent of <simpleStmt> ( 1cf5f70 )
a		30		ID		---		<assignmentStmt> (1cf8cf0)		YES		---
<simpleStmt> ( 1cf8c60 ) parent of <assignmentStmt> ( 1cf8cf0 )
:=		30		ASSIGNOP		---		<assignmentStmt> (1cf8cf0)		YES		---
t		30		ID		---		<var> (1cf9690)		YES		---
AND ( 1cf9180 ) parent of <var> ( 1cf9690 )
<expression> ( 1cf8ed0 ) parent of AND ( 1cf9180 )
list		30		ID		---		<var> (1cfa0c0)		YES		---
PLUS ( 1cf9d60 ) parent of <var> ( 1cfa0c0 )
12		30		NUM		12		<index> (1cfa330)		YES		---
<var> ( 1cfa0c0 ) parent of <index> ( 1cfa330 )
AND ( 1cf9180 ) parent of PLUS ( 1cf9d60 )
5.3		30		RNUM		5.3		<var> (1cfaa30)		YES		---
PLUS ( 1cf9d60 ) parent of <var> ( 1cfaa30 )
<assignmentStmt> ( 1cf8cf0 ) parent of <expression> ( 1cf8ed0 )
<statements> ( 1cde310 ) parent of <simpleStmt> ( 1cf8c60 )
end		31		END		---		<iterativeStmt> (1cde050)		YES		---
for		32		FOR		---		<iterativeStmt> (1cfb030)		YES		---
<statements> ( 1cdaaf0 ) parent of <iterativeStmt> ( 1cfb030 )
index		32		ID		---		<iterativeStmt> (1cfb030)		YES		---
1		32		NUM		1		<range> (1cfb280)		YES		---
<iterativeStmt> ( 1cfb030 ) parent of <range> ( 1cfb280 )
15		32		NUM		15		<range> (1cfb280)		YES		---
start		33		START		---		<iterativeStmt> (1cfb030)		YES		---
y_1		34		ID		---		<idList> (1cfbc70)		YES		---
<declareStmt> ( 1cfbb70 ) parent of <idList> ( 1cfbc70 )
y_2		34		ID		---		<idList> (1cfbc70)		YES		---
<statements> ( 1cfb3d0 ) parent of <declareStmt> ( 1cfbb70 )
real		34		REAL		---		<dataType> (1cfbd50)		YES		---
<declareStmt> ( 1cfbb70 ) parent of <dataType> ( 1cfbd50 )
<iterativeStmt> ( 1cfb030 ) parent of <statements> ( 1cfb3d0 )
k		35		ID		---		<idList> (1cfc7a0)		YES		---
<declareStmt> ( 1cfc6a0 ) parent of <idList> ( 1cfc7a0 )
l		35		ID		---		<idList> (1cfc7a0)		YES		---
m		35		ID		---		<idList> (1cfc7a0)		YES		---
<statements> ( 1cfb3d0 ) parent of <declareStmt> ( 1cfc6a0 )
array		35		ARRAY		---		<dataType> (1cfc880)		YES		---
<declareStmt> ( 1cfc6a0 ) parent of <dataType> ( 1cfc880 )
1		35		NUM		1		<range> (1cfd220)		YES		---
<dataType> ( 1cfc880 ) parent of <range> ( 1cfd220 )
10		35		NUM		10		<range> (1cfd220)		YES		---
real		35		REAL		---		<dataType> (1cfc880)		YES		---
x		36		ID		---		<idList> (1cfdbd0)		YES		---
<declareStmt> ( 1cfdad0 ) parent of <idList> ( 1cfdbd0 )
<statements> ( 1cfb3d0 ) parent of <declareStmt> ( 1cfdad0 )
real		36		REAL		---		<dataType> (1cfdcb0)		YES		---
<declareStmt> ( 1cfdad0 ) parent of <dataType> ( 1cfdcb0 )
t		37		ID		---		<assignmentStmt> (1cfe440)		YES		---
<simpleStmt> ( 1cfe3b0 ) parent of <assignmentStmt> ( 1cfe440 )
:=		37		ASSIGNOP		---		<assignmentStmt> (1cfe440)		YES		---
index		37		ID		---		<var> (1cfede0)		YES		---
LE ( 1cfe960 ) parent of <var> ( 1cfede0 )
<expression> ( 1cfe620 ) parent of LE ( 1cfe960 )
n		37		ID		---		<var> (1cff660)		YES		---
LE ( 1cfe960 ) parent of <var> ( 1cff660 )
<assignmentStmt> ( 1cfe440 ) parent of <expression> ( 1cfe620 )
<statements> ( 1cfb3d0 ) parent of <simpleStmt> ( 1cfe3b0 )
t		38		ID		---		<var> (1d00760)		YES		---
<expression> ( 1cffe10 ) parent of <var> ( 1d00760 )
<condionalStmt> ( 1cffca0 ) parent of <expression> ( 1cffe10 )
<statements> ( 1cfb3d0 ) parent of <condionalStmt> ( 1cffca0 )
start		39		START		---		<condionalStmt> (1cffca0)		YES		---
true		40		TRUE		---		<value> (1d00d40)		YES		---
<caseStmts> ( 1cfff60 ) parent of <value> ( 1d00d40 )
<condionalStmt> ( 1cffca0 ) parent of <caseStmts> ( 1cfff60 )
print		40		PRINT		---		<ioStmt> (1d01360)		YES		---
<statements> ( 1d00e20 ) parent of <ioStmt> ( 1d01360 )
list		40		ID		---		<var> (1d014d0)		YES		---
<ioStmt> ( 1d01360 ) parent of <var> ( 1d014d0 )
index		40		ID		---		<index> (1d01940)		YES		---
<var> ( 1d014d0 ) parent of <index> ( 1d01940 )
<caseStmts> ( 1cfff60 ) parent of <statements> ( 1d00e20 )
m		41		ID		---		<assignmentStmt> (1d01e50)		YES		---
<simpleStmt> ( 1d01dc0 ) parent of <assignmentStmt> ( 1d01e50 )
j		41		ID		---		<index> (1d02270)		YES		---
<assignmentStmt> ( 1d01e50 ) parent of <index> ( 1d02270 )
:=		41		ASSIGNOP		---		<assignmentStmt> (1d01e50)		YES		---
k		41		ID		---		<var> (1d02a90)		YES		---
PLUS ( 1d02730 ) parent of <var> ( 1d02a90 )
j		41		ID		---		<index> (1d02d00)		YES		---
<var> ( 1d02a90 ) parent of <index> ( 1d02d00 )
<expression> ( 1d02030 ) parent of PLUS ( 1d02730 )
34.5		41		RNUM		34.5		<var> (1d03400)		YES		---
PLUS ( 1d02730 ) parent of <var> ( 1d03400 )
<assignmentStmt> ( 1d01e50 ) parent of <expression> ( 1d02030 )
<statements> ( 1d00e20 ) parent of <simpleStmt> ( 1d01dc0 )
sum		42		ID		---		<assignmentStmt> (1d039b0)		YES		---
<simpleStmt> ( 1d03920 ) parent of <assignmentStmt> ( 1d039b0 )
:=		42		ASSIGNOP		---		<assignmentStmt> (1d039b0)		YES		---
sum		42		ID		---		<var> (1d04350)		YES		---
PLUS ( 1d03ff0 ) parent of <var> ( 1d04350 )
<expression> ( 1d03b90 ) parent of PLUS ( 1d03ff0 )
list		42		ID		---		<var> (1d04a20)		YES		---
PLUS ( 1d04180 ) parent of <var> ( 1d04a20 )
index		42		ID		---		<index> (1d04c90)		YES		---
<var> ( 1d04a20 ) parent of <index> ( 1d04c90 )
PLUS ( 1d03ff0 ) parent of PLUS ( 1d04180 )
k		42		ID		---		<var> (1d05390)		YES		---
PLUS ( 1d04180 ) parent of <var> ( 1d05390 )
index		42		ID		---		<index> (1d05600)		YES		---
<var> ( 1d05390 ) parent of <index> ( 1d05600 )
<assignmentStmt> ( 1d039b0 ) parent of <expression> ( 1d03b90 )
<statements> ( 1d00e20 ) parent of <simpleStmt> ( 1d03920 )
value		43		ID		---		<assignmentStmt> (1d05d00)		YES		---
<simpleStmt> ( 1d05c70 ) parent of <assignmentStmt> ( 1d05d00 )
:=		43		ASSIGNOP		---		<assignmentStmt> (1d05d00)		YES		---
sum		43		ID		---		<var> (1d066a0)		YES		---
PLUS ( 1d06340 ) parent of <var> ( 1d066a0 )
<expression> ( 1d05ee0 ) parent of PLUS ( 1d06340 )
15		43		NUM		15		<var> (1d06d70)		YES		---
PLUS ( 1d06340 ) parent of <var> ( 1d06d70 )
<assignmentStmt> ( 1d05d00 ) parent of <expression> ( 1d05ee0 )
<statements> ( 1d00e20 ) parent of <simpleStmt> ( 1d05c70 )
x_2		44		ID		---		<assignmentStmt> (1d07320)		YES		---
<simpleStmt> ( 1d07290 ) parent of <assignmentStmt> ( 1d07320 )
:=		44		ASSIGNOP		---		<assignmentStmt> (1d07320)		YES		---
x_1		44		ID		---		<var> (1d07cc0)		YES		---
PLUS ( 1d07960 ) parent of <var> ( 1d07cc0 )
<expression> ( 1d07500 ) parent of PLUS ( 1d07960 )
x_2		44		ID		---		<var> (1d08390)		YES		---
PLUS ( 1d07960 ) parent of <var> ( 1d08390 )
<assignmentStmt> ( 1d07320 ) parent of <expression> ( 1d07500 )
<statements> ( 1d00e20 ) parent of <simpleStmt> ( 1d07290 )
x_1		45		ID		---		<assignmentStmt> (1d08a60)		YES		---
<simpleStmt> ( 1d089d0 ) parent of <assignmentStmt> ( 1d08a60 )
:=		45		ASSIGNOP		---		<assignmentStmt> (1d08a60)		YES		---
11		45		NUM		11		<var> (1d09400)		YES		---
PLUS ( 1d090a0 ) parent of <var> ( 1d09400 )
<expression> ( 1d08c40 ) parent of PLUS ( 1d090a0 )
index		45		ID		---		<var> (1d099b0)		YES		---
PLUS ( 1d090a0 ) parent of <var> ( 1d099b0 )
<assignmentStmt> ( 1d08a60 ) parent of <expression> ( 1d08c40 )
<statements> ( 1d00e20 ) parent of <simpleStmt> ( 1d089d0 )
x_1		46		ID		---		<idList> (1d0a0f0)		YES		---
<declareStmt> ( 1d09ff0 ) parent of <idList> ( 1d0a0f0 )
x_2		46		ID		---		<idList> (1d0a0f0)		YES		---
<statements> ( 1d00e20 ) parent of <declareStmt> ( 1d09ff0 )
integer		46		INTEGER		---		<dataType> (1d0a1d0)		YES		---
<declareStmt> ( 1d09ff0 ) parent of <dataType> ( 1d0a1d0 )
u1		47		ID		---		<idList> (1d0ac20)		YES		---
<declareStmt> ( 1d0ab20 ) parent of <idList> ( 1d0ac20 )
u2		47		ID		---		<idList> (1d0ac20)		YES		---
<statements> ( 1d00e20 ) parent of <declareStmt> ( 1d0ab20 )
real		47		REAL		---		<dataType> (1d0ad00)		YES		---
<declareStmt> ( 1d0ab20 ) parent of <dataType> ( 1d0ad00 )
u2		48		ID		---		<assignmentStmt> (1d0b6e0)		YES		---
<simpleStmt> ( 1d0b650 ) parent of <assignmentStmt> ( 1d0b6e0 )
:=		48		ASSIGNOP		---		<assignmentStmt> (1d0b6e0)		YES		---
n		48		ID		---		<var> (1d0c080)		YES		---
PLUS ( 1d0bd20 ) parent of <var> ( 1d0c080 )
<expression> ( 1d0b8c0 ) parent of PLUS ( 1d0bd20 )
u1		48		ID		---		<var> (1d0c750)		YES		---
MUL ( 1d0c410 ) parent of <var> ( 1d0c750 )
PLUS ( 1d0bd20 ) parent of MUL ( 1d0c410 )
23.5		48		RNUM		23.5		<var> (1d0cc70)		YES		---
MUL ( 1d0c410 ) parent of <var> ( 1d0cc70 )
<assignmentStmt> ( 1d0b6e0 ) parent of <expression> ( 1d0b8c0 )
<statements> ( 1d00e20 ) parent of <simpleStmt> ( 1d0b650 )
print		50		PRINT		---		<ioStmt> (1d0d830)		YES		---
<statements> ( 1d0d2f0 ) parent of <ioStmt> ( 1d0d830 )
sum		50		ID		---		<var> (1d0d9a0)		YES		---
<ioStmt> ( 1d0d830 ) parent of <var> ( 1d0d9a0 )
<caseStmts> ( 1cfff60 ) parent of <statements> ( 1d0d2f0 )
u1		51		ID		---		<idList> (1d0e0f0)		YES		---
<declareStmt> ( 1d0dff0 ) parent of <idList> ( 1d0e0f0 )
x		51		ID		---		<idList> (1d0e0f0)		YES		---
x_5		51		ID		---		<idList> (1d0e0f0)		YES		---
<statements> ( 1d0d2f0 ) parent of <declareStmt> ( 1d0dff0 )
integer		51		INTEGER		---		<dataType> (1d0e1d0)		YES		---
<declareStmt> ( 1d0dff0 ) parent of <dataType> ( 1d0e1d0 )
print		52		PRINT		---		<ioStmt> (1d0ed70)		YES		---
<statements> ( 1d0d2f0 ) parent of <ioStmt> ( 1d0ed70 )
index		52		ID		---		<var> (1d0eee0)		YES		---
<ioStmt> ( 1d0ed70 ) parent of <var> ( 1d0eee0 )
end		54		END		---		<condionalStmt> (1cffca0)		YES		---
end		55		END		---		<iterativeStmt> (1cfb030)		YES		---
print		56		PRINT		---		<ioStmt> (1d0f8b0)		YES		---
<statements> ( 1cdaaf0 ) parent of <ioStmt> ( 1d0f8b0 )
x_2		56		ID		---		<var> (1d0fa20)		YES		---
<ioStmt> ( 1d0f8b0 ) parent of <var> ( 1d0fa20 )
end		57		END		---		<moduleDef> (1cd8ca0)		YES		---
<program> ( 1cd7e60 ) parent of <otherModules> ( 1cd7fb0 )
start		59		START		---		<moduleDef> (1d10280)		YES		---
<driverModule> ( 1cd8020 ) parent of <moduleDef> ( 1d10280 )
A		60		ID		---		<idList> (1d108f0)		YES		---
<declareStmt> ( 1d107f0 ) parent of <idList> ( 1d108f0 )
<statements> ( 1d10540 ) parent of <declareStmt> ( 1d107f0 )
array		60		ARRAY		---		<dataType> (1d109d0)		YES		---
<declareStmt> ( 1d107f0 ) parent of <dataType> ( 1d109d0 )
1		60		NUM		1		<range> (1d10ed0)		YES		---
<dataType> ( 1d109d0 ) parent of <range> ( 1d10ed0 )
15		60		NUM		15		<range> (1d10ed0)		YES		---
real		60		REAL		---		<dataType> (1d109d0)		YES		---
<moduleDef> ( 1d10280 ) parent of <statements> ( 1d10540 )
k		61		ID		---		<idList> (1d11880)		YES		---
<declareStmt> ( 1d11780 ) parent of <idList> ( 1d11880 )
<statements> ( 1d10540 ) parent of <declareStmt> ( 1d11780 )
integer		61		INTEGER		---		<dataType> (1d11960)		YES		---
<declareStmt> ( 1d11780 ) parent of <dataType> ( 1d11960 )
s		62		ID		---		<idList> (1d12160)		YES		---
<declareStmt> ( 1d12060 ) parent of <idList> ( 1d12160 )
<statements> ( 1d10540 ) parent of <declareStmt> ( 1d12060 )
real		62		REAL		---		<dataType> (1d12240)		YES		---
<declareStmt> ( 1d12060 ) parent of <dataType> ( 1d12240 )
get_value		63		GET_VALUE		---		<ioStmt> (1d12940)		YES		---
<statements> ( 1d10540 ) parent of <ioStmt> ( 1d12940 )
k		63		ID		---		<ioStmt> (1d12940)		YES		---
readArr		64		ID		---		<moduleReuseStmt> (1d13100)		YES		---
<simpleStmt> ( 1d13070 ) parent of <moduleReuseStmt> ( 1d13100 )
A		64		ID		---		<idList> (1d13430)		YES		---
<moduleReuseStmt> ( 1d13100 ) parent of <idList> ( 1d13430 )
u1		64		ID		---		<idList> (1d13430)		YES		---
<statements> ( 1d10540 ) parent of <simpleStmt> ( 1d13070 )
s		65		ID		---		<idList> (1d14400)		YES		---
<optional> ( 1d13f10 ) parent of <idList> ( 1d14400 )
<moduleReuseStmt> ( 1d13e80 ) parent of <optional> ( 1d13f10 )
:=		65		ASSIGNOP		---		<optional> (1d13f10)		YES		---
<simpleStmt> ( 1d13df0 ) parent of <moduleReuseStmt> ( 1d13e80 )
arraySum		65		ID		---		<moduleReuseStmt> (1d13e80)		YES		---
A		65		ID		---		<idList> (1d141b0)		YES		---
<moduleReuseStmt> ( 1d13e80 ) parent of <idList> ( 1d141b0 )
k		65		ID		---		<idList> (1d141b0)		YES		---
<statements> ( 1d10540 ) parent of <simpleStmt> ( 1d13df0 )
print		66		PRINT		---		<ioStmt> (1d15010)		YES		---
<statements> ( 1d10540 ) parent of <ioStmt> ( 1d15010 )
s		66		ID		---		<var> (1d15180)		YES		---
<ioStmt> ( 1d15010 ) parent of <var> ( 1d15180 )
end		67		END		---		<moduleDef> (1d10280)		YES		---
<program> ( 1cd7e60 ) parent of <driverModule> ( 1cd8020 )
readArr		69		ID		---		<module> (1d15790)		YES		---
<otherModules> ( 1cd8090 ) parent of <module> ( 1d15790 )
arr1		70		ID		---		<input_plist> (1d15bc0)		YES		---
<module> ( 1d15790 ) parent of <input_plist> ( 1d15bc0 )
array		70		ARRAY		---		<dataType> (1d16280)		YES		---
<input_plist> ( 1d15bc0 ) parent of <dataType> ( 1d16280 )
1		70		NUM		1		<range> (1d16560)		YES		---
<dataType> ( 1d16280 ) parent of <range> ( 1d16560 )
15		70		NUM		15		<range> (1d16560)		YES		---
boolean		70		BOOLEAN		---		<dataType> (1d16280)		YES		---
k		70		ID		---		<input_plist> (1d15bc0)		YES		---
integer		70		INTEGER		---		<dataType> (1d16df0)		YES		---
<input_plist> ( 1d15bc0 ) parent of <dataType> ( 1d16df0 )
start		71		START		---		<moduleDef> (1d15d80)		YES		---
<module> ( 1d15790 ) parent of <moduleDef> ( 1d15d80 )
tempvar		72		ID		---		<idList> (1d177b0)		YES		---
<declareStmt> ( 1d176b0 ) parent of <idList> ( 1d177b0 )
<statements> ( 1d17400 ) parent of <declareStmt> ( 1d176b0 )
real		72		REAL		---		<dataType> (1d17890)		YES		---
<declareStmt> ( 1d176b0 ) parent of <dataType> ( 1d17890 )
<moduleDef> ( 1d15d80 ) parent of <statements> ( 1d17400 )
i		73		ID		---		<idList> (1d18090)		YES		---
<declareStmt> ( 1d17f90 ) parent of <idList> ( 1d18090 )
<statements> ( 1d17400 ) parent of <declareStmt> ( 1d17f90 )
integer		73		INTEGER		---		<dataType> (1d18170)		YES		---
<declareStmt> ( 1d17f90 ) parent of <dataType> ( 1d18170 )
i		74		ID		---		<assignmentStmt> (1d18900)		YES		---
<simpleStmt> ( 1d18870 ) parent of <assignmentStmt> ( 1d18900 )
:=		74		ASSIGNOP		---		<assignmentStmt> (1d18900)		YES		---
1		74		NUM		1		<var> (1d192a0)		YES		---
<expression> ( 1d18ae0 ) parent of <var> ( 1d192a0 )
<assignmentStmt> ( 1d18900 ) parent of <expression> ( 1d18ae0 )
<statements> ( 1d17400 ) parent of <simpleStmt> ( 1d18870 )
x_1		75		ID		---		<assignmentStmt> (1d19850)		YES		---
<simpleStmt> ( 1d197c0 ) parent of <assignmentStmt> ( 1d19850 )
:=		75		ASSIGNOP		---		<assignmentStmt> (1d19850)		YES		---
i		75		ID		---		<var> (1d1a1f0)		YES		---
PLUS ( 1d19e90 ) parent of <var> ( 1d1a1f0 )
<expression> ( 1d19a30 ) parent of PLUS ( 1d19e90 )
u1		75		ID		---		<var> (1d1a8c0)		YES		---
PLUS ( 1d19e90 ) parent of <var> ( 1d1a8c0 )
<assignmentStmt> ( 1d19850 ) parent of <expression> ( 1d19a30 )
<statements> ( 1d17400 ) parent of <simpleStmt> ( 1d197c0 )
i		76		ID		---		<idList> (1d1b000)		YES		---
<declareStmt> ( 1d1af00 ) parent of <idList> ( 1d1b000 )
<statements> ( 1d17400 ) parent of <declareStmt> ( 1d1af00 )
real		76		REAL		---		<dataType> (1d1b0e0)		YES		---
<declareStmt> ( 1d1af00 ) parent of <dataType> ( 1d1b0e0 )
while		77		WHILE		---		<iterativeStmt> (1d1b7e0)		YES		---
<statements> ( 1d17400 ) parent of <iterativeStmt> ( 1d1b7e0 )
i		77		ID		---		<var> (1d1c180)		YES		---
LE ( 1d1bd00 ) parent of <var> ( 1d1c180 )
<iterativeStmt> ( 1d1b7e0 ) parent of LE ( 1d1bd00 )
k		77		ID		---		<var> (1d1ca00)		YES		---
LE ( 1d1bd00 ) parent of <var> ( 1d1ca00 )
start		78		START		---		<iterativeStmt> (1d1b7e0)		YES		---
x_1		79		ID		---		<idList> (1d1d190)		YES		---
<declareStmt> ( 1d1d090 ) parent of <idList> ( 1d1d190 )
x_2		79		ID		---		<idList> (1d1d190)		YES		---
<statements> ( 1d1baa0 ) parent of <declareStmt> ( 1d1d090 )
boolean		79		BOOLEAN		---		<dataType> (1d1d270)		YES		---
<declareStmt> ( 1d1d090 ) parent of <dataType> ( 1d1d270 )
<iterativeStmt> ( 1d1b7e0 ) parent of <statements> ( 1d1baa0 )
x_1		80		ID		---		<assignmentStmt> (1d1dc50)		YES		---
<simpleStmt> ( 1d1dbc0 ) parent of <assignmentStmt> ( 1d1dc50 )
:=		80		ASSIGNOP		---		<assignmentStmt> (1d1dc50)		YES		---
true		80		TRUE		---		<var> (1d1e5f0)		YES		---
AND ( 1d1e0e0 ) parent of <var> ( 1d1e5f0 )
<expression> ( 1d1de30 ) parent of AND ( 1d1e0e0 )
u2		80		ID		---		<var> (1d1ef00)		YES		---
LE ( 1d1e980 ) parent of <var> ( 1d1ef00 )
AND ( 1d1e0e0 ) parent of LE ( 1d1e980 )
10		80		NUM		10		<var> (1d1f780)		YES		---
LE ( 1d1e980 ) parent of <var> ( 1d1f780 )
<assignmentStmt> ( 1d1dc50 ) parent of <expression> ( 1d1de30 )
<statements> ( 1d1baa0 ) parent of <simpleStmt> ( 1d1dbc0 )
get_value		81		GET_VALUE		---		<ioStmt> (1d1fca0)		YES		---
<statements> ( 1d1baa0 ) parent of <ioStmt> ( 1d1fca0 )
tempvar		81		ID		---		<ioStmt> (1d1fca0)		YES		---
x_1		82		ID		---		<idList> (1d204d0)		YES		---
<declareStmt> ( 1d203d0 ) parent of <idList> ( 1d204d0 )
x_3		82		ID		---		<idList> (1d204d0)		YES		---
<statements> ( 1d1baa0 ) parent of <declareStmt> ( 1d203d0 )
integer		82		INTEGER		---		<dataType> (1d205b0)		YES		---
<declareStmt> ( 1d203d0 ) parent of <dataType> ( 1d205b0 )
arr1		83		ID		---		<assignmentStmt> (1d20f90)		YES		---
<simpleStmt> ( 1d20f00 ) parent of <assignmentStmt> ( 1d20f90 )
i		83		ID		---		<index> (1d213b0)		YES		---
<assignmentStmt> ( 1d20f90 ) parent of <index> ( 1d213b0 )
:=		83		ASSIGNOP		---		<assignmentStmt> (1d20f90)		YES		---
tempvar		83		ID		---		<var> (1d21bd0)		YES		---
<expression> ( 1d21170 ) parent of <var> ( 1d21bd0 )
<assignmentStmt> ( 1d20f90 ) parent of <expression> ( 1d21170 )
<statements> ( 1d1baa0 ) parent of <simpleStmt> ( 1d20f00 )
i		84		ID		---		<assignmentStmt> (1d222a0)		YES		---
<simpleStmt> ( 1d22210 ) parent of <assignmentStmt> ( 1d222a0 )
:=		84		ASSIGNOP		---		<assignmentStmt> (1d222a0)		YES		---
i		84		ID		---		<var> (1d22c40)		YES		---
PLUS ( 1d228e0 ) parent of <var> ( 1d22c40 )
<expression> ( 1d22480 ) parent of PLUS ( 1d228e0 )
1		84		NUM		1		<var> (1d23310)		YES		---
PLUS ( 1d228e0 ) parent of <var> ( 1d23310 )
<assignmentStmt> ( 1d222a0 ) parent of <expression> ( 1d22480 )
<statements> ( 1d1baa0 ) parent of <simpleStmt> ( 1d22210 )
end		85		END		---		<iterativeStmt> (1d1b7e0)		YES		---
x_1		86		ID		---		<idList> (1d23a10)		YES		---
<declareStmt> ( 1d23910 ) parent of <idList> ( 1d23a10 )
x_2		86		ID		---		<idList> (1d23a10)		YES		---
x_3		86		ID		---		<idList> (1d23a10)		YES		---
<statements> ( 1d17400 ) parent of <declareStmt> ( 1d23910 )
boolean		86		BOOLEAN		---		<dataType> (1d23af0)		YES		---
<declareStmt> ( 1d23910 ) parent of <dataType> ( 1d23af0 )
end		87		END		---		<moduleDef> (1d15d80)		YES		---
<program> ( 1cd7e60 ) parent of <otherModules> ( 1cd8090 )
