# Project Structure

```
lexiTree/
├── data/
│   └── dictionary.txt
├── docs/
│   ├── AGENT.md
│   ├── PROJECT_GUIDE.md
│   ├── ROADMAP.md
│   ├── addendum-functions-and-ambiguity.md
│   └── plan.md
├── include/
│   ├── bottom_up_parser.h
│   ├── display.h
│   ├── lexer.h
│   ├── parse_tree.h
│   ├── pos_dict.h
│   ├── symbol_table.h
│   └── top_down_parser.h
├── scripts/
│   └── run_smoke_tests
├── src/
│   ├── bottom_up_parser.cpp
│   ├── bottom_up_parser.cpp_new
│   ├── display.cpp
│   ├── lexer.cpp
│   ├── main.cpp
│   ├── parse_tree.cpp
│   ├── pos_dict.cpp
│   ├── symbol_table.cpp
│   └── top_down_parser.cpp
├── README.md
└── justfile
```

# Project Files

## File: `data/dictionary.txt`

```text

#
ability N
able ADJ
aboard PREP
about PREP
above PREP
abroad ADV
absent ADJ
absolutely INTJ
academic ADJ
academically ADV
accepted V
accepting V
accepts V
accept V
accordingly CONJ
achieveed V
achieveing V
achieves V
achieve V
across PREP
activist N
actor N
actually ADV
# Add custom words at the bottom of this file.
added V
adding V
additional ADJ
additionally CONJ
adds V
add V
a DET
# ── ADJ (adjectives) ──
admired V
admires V
admire V
admiring V
adult N
# ── ADV (adverbs) ──
advanced ADJ
adviseed V
adviseing V
advises V
advise V
affected V
affecting V
affects V
affect V
afraid ADJ
africa N
african N
after CONJ
afternoon N
again ADV
against PREP
ago ADV
agreed V
agreeed V
agreeing V
agrees V
agree V
agriculture N
ahead ADV
ah INTJ
aint AUX
air N
airport N
airports N
alas INTJ
alive ADJ
aliver ADJ
alivest ADJ
all DET
allowed V
allowing V
allows V
allow V
almost ADV
along PREP
already ADV
alternatively CONJ
although CONJ
always ADV
am AUX
amazing ADJ
amid PREP
amidst PREP
among PREP
amongst PREP
amount N
analytical ADJ
analyzeed V
analyzeing V
analyzes V
analyze V
ancestor N
ancient ADJ
and CONJ
an DET
anger N
angrier ADJ
angriest ADJ
angry ADJ
animal N
animals N
ankle N
ankles N
announceed V
announceing V
announces V
announce V
annual ADJ
annually ADV
another PRON
answered V
answering V
answer N
answers N
ant N
ants N
anxious ADJ
any DET
anyone PRON
anything PRON
anywhere PRON
apartment N
apartments N
ape N
apes N
apologizeed V
apologizeing V
apologizes V
apologize V
apparently INTJ
appeared V
appearing V
appears V
appear V
approved ADJ
approximately ADV
architect N
area N
are AUX
arent AUX
argueed V
argueing V
argues V
argue V
arm N
arms N
around PREP
arriveed V
arriveing V
arrives V
arrive V
arrow N
arrows N
arteries N
artery N
artificially ADV
artist N
art N
asante N
as CONJ
ashamed ADJ
ash N
aside PREP
asked V
asking V
asks V
ask V
as long as CONJ
aspect N
assignment N
as soon as CONJ
assumed V
assumes V
assume V
assuming CONJ
astronaut N
ate V
athlete N
atop PREP
at PREP
attached V
attaching V
attachs V
attach V
attacked V
attacking V
attacks V
attack V
attended V
attending V
attends V
attend V
attitude N
aunt N
automatically ADV
# ── AUX (auxiliaries) ──
available ADJ
average N
away ADV
awful ADJ
baba N
baby N
back ADV
bad ADJ
badly ADV
bado N
bag N
bags N
bakeed V
bakeing V
bakes V
bake V
ball N
balls N
baraza N
barely ADV
basic ADJ
basically INTJ
bay N
bays N
beaches N
beach N
bear N
bears N
beast N
beasts N
beaten V
beating V
beats V
beat V
beautiful ADJ
beauty N
be AUX
became V
because CONJ
becomes V
become V
becoming V
bed N
beds N
bee N
been AUX
beer N
bees N
before CONJ
before PREP
began V
beged V
beging V
beginning V
begins V
begin V
begs V
begun V
beg V
behavior N
behind PREP
beige ADJ
being AUX
believed V
believeed V
believeing V
believes V
believe V
believing V
belly N
belonged V
belonging V
belongs V
belong V
below PREP
bending V
bends V
bend V
beneath PREP
bent V
beside PREP
besides CONJ
best ADJ
better ADJ
between PREP
beyond PREP
big ADJ
bigger ADJ
biggest ADJ
bike N
bikes N
billion NUM
bill N
bills N
biological ADJ
bird N
birds N
bites V
bite V
biting V
bitten V
bit V
black ADJ
blameed V
blameing V
blames V
blame V
blew V
blocked V
blocking V
blocks V
block V
blood N
blowing V
blown V
blows V
blow V
blue ADJ
blunt ADJ
board N
boat N
boats N
boma N
bone N
bones N
bony ADJ
book N
books N
bored ADJ
boss N
bossy ADJ
both DET
bottle N
bottles N
bottom ADJ
bought V
bounty ADJ
bowl N
bowls N
bow N
bows N
boxes N
box N
boy N
bracelet N
brain N
branches N
branch N
brave ADJ
braver ADJ
bravest ADJ
bread N
breaked V
breakfast N
breaking V
break N
breaks V
break V
breatheed V
breatheing V
breathes V
breathe V
breezy ADJ
bridge N
bridges N
brief ADJ
bright ADJ
bringing V
brings V
bring V
broad ADJ
broadly ADV
broken V
broke V
brother N
brought V
brown ADJ
builded V
builder N
builders N
buildings N
building V
building N
builds V
build V
built V
bully ADJ
bumpy ADJ
burly ADJ
buses N
busier ADJ
busiest ADJ
business N
bus N
busty ADJ
busy ADJ
but CONJ
butterflies N
butterfly N
button N
buttons N
buying V
buys V
buy V
bye INTJ
by PREP
cable N
cables N
cake N
calculateed V
calculateing V
calculates V
calculate V
called V
calling V
calls V
call V
calm ADJ
camera N
cameras N
came V
campus N
can AUX
cant AUX
capable ADJ
captain N
card N
cards N
careed V
carefully ADV
careing V
carelessly ADV
cares V
care V
car N
carried V
carries V
carrying V
carry V
cars N
case N
cases N
cash N
catches V
catching V
catch V
cat N
cats N
caught V
causeed V
causeing V
cause N
causes N
cave N
caves N
ceiling N
ceilings N
central ADJ
certainly INTJ
chai N
chain N
chains N
chair N
chairs N
champion N
chance N
changed V
changeed V
changeing V
changes V
change V
changing V
character N
charger N
checked V
checking V
checks V
check V
cheek N
chef N
chemical ADJ
chest N
chicken N
chickens N
chief N
child N
children N
chilly ADJ
chimpanzee N
chimpanzees N
chin N
choice N
chooses V
choose V
choosing V
chosen V
chose V
christmas PROPER_N
churches N
church N
circular ADJ
circumstance N
circumstances N
citizen N
claimed V
claiming V
claims V
claim V
classic ADJ
classmate N
class N
classy ADJ
clean ADJ
cleaned V
cleaning V
cleanr ADJ
cleanst ADJ
cleans V
clear ADJ
clearly INTJ
clever ADJ
cliff N
cliffs N
climate N
climbed V
climber N
climbers N
climbing V
climbs V
climb V
clock N
clocks N
closed V
closely ADV
closer ADJ
closest ADJ
closes V
close V
closing V
cloth N
cloud N
clouds N
clumpy ADJ
coach N
coast N
coasts N
coat N
coffee N
coin N
coins N
cold ADJ
colder ADJ
coldest ADJ
collected V
collecting V
collection N
collective ADJ
collects V
collect V
college N
colored V
colorful ADJ
coloring V
color N
colors V
coloured V
colourful ADJ
colouring V
colours N
colour V
combined V
combines V
combine V
combining V
comes V
come V
comfortable ADJ
coming V
common ADJ
community N
compareed V
compareing V
compares V
compare V
complained V
complaining V
complains V
complain V
complete ADJ
completeed V
completeing V
completely ADV
completes V
complex ADJ
computer N
computers N
concerning PREP
condition N
conditions N
confirmed V
confirming V
confirms V
confirm V
confused ADJ
# ── CONJ (conjunctions) ──
connected V
connecting V
connection N
connections N
connects V
connect V
consequently CONJ
considered V
considering V
considers V
consider V
constantly ADV
constructed V
constructing V
constructs V
construct V
consultant N
contained V
containing V
contains V
contain V
continued V
continueed V
continueing V
continues V
continue V
continuing V
continuously ADV
controled V
controling V
controlled V
controlling V
controls V
control V
cooked V
cooker N
cookie N
cookies N
cooking V
cooks V
cook V
cool ADJ
cooled V
cooler ADJ
coolest ADJ
cooling V
cools V
copyed V
copying V
copys V
copy V
coral ADJ
correct ADJ
costly ADJ
cost N
costs N
cosy ADJ
could AUX
couldnt AUX
counted V
counting V
countless ADJ
country N
counts V
count V
county ADJ
couple N
court N
courts N
cousin N
cowardly ADJ
cow N
cows N
cozy ADJ
crawled V
crawling V
crawls V
crawl V
crazy ADJ
cream ADJ
creamy ADJ
created V
creates V
create V
creating V
creative ADJ
creatively ADV
creature N
creatures N
creeping V
creeps V
creep V
crept V
cried V
cries V
criminal N
crimson ADJ
crinkly ADJ
critical ADJ
criticizeed V
criticizeing V
criticizes V
criticize V
critic N
crocodile N
crocodiles N
crossed V
crossing V
crosss V
cross V
crow N
crows N
crude ADJ
cruder ADJ
crudest ADJ
cruel ADJ
crusty ADJ
crying V
cry V
cultural ADJ
culturally ADV
culture N
cup N
cups N
curious ADJ
curly ADJ
current ADJ
currently ADV
currents N
curved ADJ
# ── CUSTOM FIXES ──
cuted V
cuting V
cuts V
cutted V
cutting V
cut V
cyan ADJ
daily ADV
dainty ADJ
danced V
danceed V
danceing V
dancer N
dancers N
dances V
dance V
dancing V
dare AUX
dark ADJ
darkness N
data N
daughter N
dawn N
day N
days N
dead ADJ
dealing V
deals V
dealt V
deal V
death N
decided V
decides V
decide V
deciding V
declareed V
declareing V
declares V
declare V
decreased V
decreaseed V
decreaseing V
decreases V
decrease V
decreasing V
deep ADJ
deeper ADJ
deepest ADJ
deeply ADV
deer N
defended V
defending V
defends V
defend V
definitely INTJ
degree N
deleteed V
deleteing V
deletes V
delete V
demanded V
demanding V
demands V
demand V
dentist N
denyed V
denying V
denys V
deny V
depended V
depending V
depends V
depend V
depth N
descendant N
described V
describeed V
describeing V
describes V
describe V
describing V
desert N
deserts N
deserveed V
deserveing V
deserves V
deserve V
designed V
designer N
designing V
designs V
design V
desk N
desks N
despite PREP
destroyed V
destroying V
destroys V
destroy V
detailed ADJ
# ── DET (determiners) ──
detected V
detecting V
detective N
detects V
detect V
developed V
developer N
developing V
development N
develops V
develop V
device N
devices N
diagonal ADJ
dice N
dicey ADJ
did AUX
didnt AUX
difference N
differences N
digital ADJ
dinner N
directed V
directing V
direction N
directly ADV
director N
directs V
direct V
dirtier ADJ
dirtiest ADJ
dirt N
dirty ADJ
disagreeed V
disagreeing V
disagrees V
disagree V
discovered V
discovering V
discovers V
discover V
discussed V
discussing V
discusss V
discuss V
dishonest ADJ
distance N
distant ADJ
distributeed V
distributeing V
distributes V
distribute V
divided V
divides V
divide V
dividing V
do AUX
doctor N
does AUX
doesnt AUX
dog N
dogs N
doing AUX
dolphin N
dolphins N
done AUX
door N
doors N
dorm N
double ADJ
doubted V
doubting V
doubts V
doubt V
down PREP
downstairs ADV
dozen NUM
drank V
drawing V
drawn V
draws V
draw V
dream N
dreams N
dreamy ADJ
dressed V
dressing V
dress N
dresss V
drew V
drier ADJ
driest ADJ
drifted V
drifting V
drifts V
drift V
drinking V
drinks V
drink V
driveed V
driveing V
driven V
driver N
drivers N
drives V
drive V
driving V
droped V
droping V
dropped V
dropping V
drops V
drop V
drove V
drunk V
dry ADJ
duck N
ducks N
during PREP
dusk N
dust N
dusty ADJ
each DET
each other PRON
eagle N
eagles N
early ADV
ear N
earned V
earning V
earns V
earn V
earring N
ears N
earth N
earthy ADJ
easier ADJ
easiest ADJ
easily ADV
east ADV
eastern N
easy ADJ
eaten V
eating V
eats V
eat V
economic ADJ
economy N
editor N
educational ADJ
education N
effectively ADV
effect N
effects N
eighteen NUM
eighth NUM
eight NUM
eighty NUM
either DET
elbow N
elbows N
eldoret N
elections N
electrical ADJ
electronic ADJ
elephant N
elephants N
eleven NUM
eleventh NUM
elk N
emotionally ADV
empirical ADJ
employee N
empty ADJ
emptyed V
emptying V
emptys V
enableed V
enableing V
enables V
enable V
ended V
ending V
ends V
end V
enemy N
engineer N
engine N
engines N
# English POS Dictionary for Parser
enjoyed V
enjoying V
enjoys V
enjoy V
enormous ADJ
enough DET
entered V
entering V
enters V
enter V
entirely ADV
environmental ADJ
environment N
equaled V
equaling V
equals V
equal V
especially ADV
essential ADJ
essentially ADV
estimateed V
estimateing V
estimates V
estimate V
ethical ADJ
evaluateed V
evaluateing V
evaluates V
evaluate V
even CONJ
even if CONJ
evening N
even though CONJ
event N
events N
eventual ADJ
eventually CONJ
everybody PRON
every DET
everyone PRON
everything PRON
everywhere PRON
evil N
exactly INTJ
examineed V
examineing V
examines V
examine V
exam N
example N
examples N
exams N
excellent ADJ
except PREP
excited ADJ
excludeed V
excludeing V
excludes V
exclude V
excluding PREP
existed V
existing V
exists V
exist V
exited V
exiting V
exits V
exit V
expanded V
expanding V
expands V
expand V
expected V
expecting V
expects V
expect V
experience N
experiences N
experimental ADJ
expert N
explained V
explaining V
explains V
explain V
extended V
extending V
extends V
extend V
extra ADJ
extremely ADV
eye N
eyes N
fabric N
face N
fact N
factories N
factory N
failed V
failing V
fails V
failure N
fail V
fairly ADV
fallen V
falling V
falls V
fall V
familiar ADJ
family N
fancy ADJ
fantastic ADJ
far ADV
farmed V
farmer N
farmers N
farming V
farms V
farm V
fast ADV
fat ADJ
father N
fatter ADJ
fattest ADJ
feared V
fearing V
fear N
fears V
feeded V
feeding V
feeds V
feed V
feeled V
feelings N
feeling V
feels V
feel V
feet N
fell V
felt V
few DET
field N
fields N
fifteen NUM
fifth NUM
fifty NUM
fighting V
fights V
fight V
files N
filled V
filling V
fills V
fill V
filthy ADJ
final ADJ
finally CONJ
financially ADV
finding V
finds V
find V
fine ADJ
finer ADJ
finest ADJ
finger N
fingers N
finished V
finishes V
finishing V
finishs V
finish V
fire N
firmly ADV
first ADV
fisherman N
fishermen N
fishes N
fish N
fits V
fitting V
fit V
five NUM
fixed ADJ
fixing V
fixs V
fix V
flame N
flat ADJ
flew V
flies V
flighty ADJ
flimsy ADJ
floated V
floating V
floats V
float V
floor N
floors N
flowed V
flower N
flowers N
flowing V
flown V
flows V
flow V
fluffy ADJ
flying V
fly V
foamy ADJ
fog N
followed V
following V
follows V
follow V
food N
foot N
for CONJ
forehead N
foreign ADJ
forest N
forests N
forgave V
forgeted V
forgeting V
forgets V
forgetting V
forget V
forgiveed V
forgiveing V
forgiven V
forgives V
forgive V
forgiving V
forgotten V
forgot V
fork N
forks N
formal ADJ
formally ADV
# Format: word TAG
formerly ADV
form N
for PREP
fortunately ADV
forty NUM
forward ADV
fought V
found V
four NUM
fourteen NUM
fourth NUM
foxes N
fox N
frankly INTJ
freckly ADJ
freedom N
freezes V
freeze V
freezing V
frequent ADJ
frequently ADV
fresh ADJ
friendly ADJ
friend N
frog N
frogs N
from PREP
front ADJ
frosty ADJ
frozen V
froze V
fruit N
fruits N
full ADJ
fully ADV
fundamental ADJ
funnier ADJ
funniest ADJ
funny ADJ
furthermore CONJ
fussy ADJ
future ADJ
gained V
gaining V
gains V
gain V
game N
games N
garden N
gardens N
garissa N
gathered V
gathering V
gathers V
gather V
gave V
gazeed V
gazeing V
gazes V
gaze V
general ADJ
generally ADV
generated V
generates V
generate V
generating V
generous ADJ
genetic ADJ
gentle ADJ
gently ADV
gets V
getting V
get V
ghostly ADJ
giant ADJ
giraffe N
giraffes N
girl N
githeri N
given V
gives V
give V
giving V
glad ADJ
gladder ADJ
gladdest ADJ
glanceed V
glanceing V
glances V
glance V
glasses N
glass N
glided V
glides V
glide V
gliding V
global ADJ
globally ADV
gloomy ADJ
glowed V
glowing V
glows V
glow V
gnarly ADJ
goal N
goals N
goat N
goats N
goes V
going V
golden ADJ
gold N
gone V
good ADJ
gorilla N
gorillas N
gotten V
got V
go V
government N
grabed V
grabing V
grabs V
grab V
gradual ADJ
gradually ADV
grandchild N
grandfather N
grandmother N
grandparent N
grass N
grateful ADJ
gray ADJ
greasy ADJ
great ADJ
greater ADJ
greatest ADJ
greedy ADJ
green ADJ
greeted V
greeting V
greets V
greet V
grew V
grey ADJ
grizzly ADJ
ground N
group N
growed V
growing V
grown V
grows V
growth N
grow V
grumpy ADJ
guard N
guessed V
guessing V
guesss V
guess V
guest N
guideed V
guideing V
guides V
guide V
guilty ADJ
gun N
guns N
gusty ADJ
gym N
gyms N
had AUX
hadnt AUX
hair N
half DET
hall N
hamster N
hamsters N
hand N
hands N
happened V
happening V
happens V
happen V
happier ADJ
happiest ADJ
happy ADJ
harambee N
harbor N
harbors N
hard ADV
harder ADJ
hardest ADJ
hardly ADV
hare N
hares N
harvested V
harvesting V
harvests V
harvest V
has AUX
hasnt AUX
hated V
hate N
hates V
hating V
hat N
have AUX
havent AUX
having AUX
hawk N
hawks N
hazy ADJ
head N
healed V
healing V
heals V
healthier ADJ
healthiest ADJ
health N
healthy ADJ
heal V
heard V
hearing V
hears V
heart N
hear V
heated V
heating V
heat N
heats V
heavier ADJ
heaviest ADJ
heavily ADV
heavy ADJ
heel N
heels N
height N
held V
helicopter N
helicopters N
hello INTJ
helped V
helping V
helps V
help V
hence CONJ
hen N
hens N
he PRON
her DET
here ADV
hero N
herself PRON
hers PRON
hey INTJ
hidden V
hides V
hide V
hiding V
hid V
high ADJ
higher ADJ
highest ADJ
highly ADV
highway N
highways N
hi INTJ
hill N
hills N
hilly ADJ
him PRON
himself PRON
hip N
hippo N
hippos N
hips N
his DET
historical ADJ
history N
hits V
hitted V
hitting V
hit V
hmm INTJ
holding V
holds V
hold V
hollow ADJ
holy ADJ
home N
homes N
honest ADJ
honestly INTJ
hooray INTJ
hoped V
hopeed V
hopefully INTJ
hopeing V
hope N
hopes V
hoping V
hops V
hop V
horizontal ADJ
horny ADJ
horse N
horses N
hospital N
hospitals N
hostel N
host N
hot ADJ
hotel N
hotels N
hotter ADJ
hottest ADJ
hour N
hours N
house N
houses N
however CONJ
huge ADJ
huger ADJ
hugest ADJ
huh INTJ
hundred NUM
hungrier ADJ
hungriest ADJ
hungry ADJ
hunted V
hunter N
hunters N
hunting V
hunts V
hunt V
hurray INTJ
hurried V
hurries V
hurrying V
hurry V
husband N
ice N
icy ADJ
ideally ADV
idea N
ideas N
if CONJ
ighty ADJ
ill ADJ
imagined V
imagineed V
imagineing V
imagines V
imagine V
imagining V
immediate ADJ
immediately ADV
immigrant N
impatient ADJ
importantly ADV
improved V
improveed V
improveing V
improvement N
improves V
improve V
improving V
in case CONJ
included V
includeed V
includeing V
includes V
include V
including V
incorrect ADJ
increased V
increaseed V
increaseing V
increases V
increase V
increasing V
incredible ADJ
incredibly ADV
indeed INTJ
independently ADV
indigo ADJ
indirectly ADV
individual ADJ
indoor ADJ
industry N
infinite ADJ
influenceed V
influenceing V
influences V
influence V
informal ADJ
informally ADV
information N
informed V
informing V
informs V
inform V
ink N
inner ADJ
in order that CONJ
in PREP
insect N
insects N
inside PREP
inspired V
inspires V
inspire V
inspiring V
instant ADJ
instantly ADV
instead CONJ
intelligent ADJ
interestingly ADV
international ADJ
# ── INTJ (interjections) ──
into PREP
introduceed V
introduceing V
introduces V
introduce V
invalid ADJ
investigateed V
investigateing V
investigates V
investigate V
inviteed V
inviteing V
invites V
invite V
inward ADV
i PRON
ironically ADV
iron N
is AUX
island N
islands N
isnt AUX
item N
items N
it PRON
its DET
itself PRON
ivory ADJ
jacket N
jambo N
jaw N
jealous ADJ
joged V
joging V
jogs V
jog V
joined V
joining V
joins V
joint N
joints N
join V
jolly ADJ
journalist N
joy N
jua N
judgeed V
judgeing V
judge N
judges V
juice N
juicy ADJ
jumped V
jumping V
jumps V
jump V
jungle N
jungles N
justice N
just INTJ
kakamega N
kalenjin N
kamba N
karibu N
keeped V
keeping V
keeps V
keep V
kenya N
kept V
key N
keys N
kicked V
kicking V
kicks V
kick V
kid N
kidney N
kidneys N
kikuyu N
killed V
killing V
kills V
kill V
kind ADJ
king N
kisumu N
kneeling V
kneels V
kneel V
knee N
knees N
knelt V
knew V
knife N
knits V
knitting V
knit V
knives N
knowing V
knowledge N
known V
knows V
know V
lacked V
lacking V
lacks V
lack V
laid V
lain V
lake N
lakes N
lamp N
lamps N
land N
language N
laptop N
laptops N
large ADJ
largely ADV
larger ADJ
largest ADJ
lasted V
lasting V
lasts V
last V
late ADV
lately ADV
laughed V
laughing V
laughs V
laugh V
law N
lawyer N
laying V
lays V
lay V
lazy ADJ
leaded V
leader N
leaders N
leading V
leads V
lead V
leaf N
leaping V
leaps V
leapt V
leap V
learned V
learning V
learns V
learn V
least DET
leaved V
leaveed V
leaveing V
leaves V
leave V
leaving V
lecture N
lecturer N
led V
left V
legal ADJ
legally ADV
leg N
legs N
length N
lengthy ADJ
less DET
lest CONJ
lets V
letter N
letters N
letting V
let V
level N
libraries N
library N
lies V
lie V
life N
lifted V
lifting V
lifts V
lift V
light ADJ
lightly ADV
lightning N
likeed V
likeing V
like PREP
likes V
like V
limited ADJ
limiting V
limits V
limit V
line N
lines N
linguistic ADJ
linked V
linking V
links V
link V
lion N
lions N
lip N
lips N
listened V
listener N
listeners N
listening V
listens V
listen V
list N
literally INTJ
literary ADJ
little DET
littler ADJ
littlest ADJ
lived V
lively ADJ
liver N
lives V
live V
living V
lizard N
lizards N
local ADJ
locally ADV
location N
lock N
locks N
lonely ADJ
long ADJ
longer ADJ
longest ADJ
looked V
looking V
looks V
look V
loosely ADV
loser N
loses V
lose V
losing V
lost V
loudly ADV
loved V
lovely ADJ
loves V
love V
loving V
low ADJ
lower ADJ
lowest ADJ
loyal ADJ
luckier ADJ
luckiest ADJ
luckily ADV
luck N
lucky ADJ
luhya N
lumpy ADJ
lunch N
lung N
lungs N
luo N
lying V
maasai N
machakos N
machine N
machines N
mad ADJ
madder ADJ
maddest ADJ
made V
magenta ADJ
main ADJ
mainly ADV
major ADJ
majority N
makes V
make V
making V
mama N
managed V
manageed V
manageing V
manager N
managers N
manages V
manage V
managing V
mandazi N
man N
manually ADV
many DET
mara N
marched V
marching V
marchs V
march V
market N
markets N
maroon ADJ
masai N
massive ADJ
matatu N
matched V
matching V
matchs V
match V
mathematical ADJ
mattered V
mattering V
matters V
matter V
may AUX
meadow N
meadows N
meal N
meals N
meaning V
means V
meant V
mean V
meanwhile CONJ
measureed V
measureing V
measures V
measure V
meat N
mechanical ADJ
medical ADJ
medicine N
meeting V
meets V
meet V
melted ADJ
memories N
memorizeed V
memorizeing V
memorizes V
memorize V
memory N
men N
mentally ADV
mentioned V
mentioning V
mentions V
mention V
me PRON
merely INTJ
mergeed V
mergeing V
merges V
merge V
message N
messier ADJ
messiest ADJ
messy ADJ
metal N
method N
methods N
met V
mice N
microscopic ADJ
middle N
midnight N
might AUX
mighty ADJ
milk N
million NUM
minded V
minding V
minds V
mind V
mine PRON
mini ADJ
minister N
minor ADJ
minority N
minus PREP
minute N
minutes N
mirror N
mirrors N
missing ADJ
mist N
misty ADJ
mixed V
mixing V
mixs V
mix V
mmu N
modern ADJ
mombasa N
moment ADJ
moments N
money N
monkey N
monkeys N
monthly ADV
month N
months N
moon N
moose N
more DET
moreover CONJ
morning N
mosque N
mosques N
mosquitoes N
mosquito N
mossy ADJ
most DET
mostly ADV
mother N
motor N
motors N
mountain N
mountains N
mouse N
mousey ADJ
mouth N
moved V
moves V
move V
moving V
mtoto N
much DET
mud N
multiple ADJ
muscle N
muscles N
museum N
museums N
musician N
music N
must AUX
mustnt AUX
musty ADJ
my DET
myself PRON
mzee N
nail N
nails N
nairobi N
nakuru N
name N
names N
narrow ADJ
narrower ADJ
narrowest ADJ
national ADJ
nationwide ADV
naturally ADV
nature N
navy ADJ
ndugu N
nearby PREP
nearly ADV
near PREP
necklace N
neck N
needed V
needing V
needs V
need V
neighbor N
neither DET
nephew N
nerve N
nerves N
nervous ADJ
never ADV
nevertheless CONJ
new ADJ
news N
next ADV
nice ADJ
nicer ADJ
nicest ADJ
niece N
night N
nighty ADJ
nine NUM
nineteen NUM
ninety NUM
ninth NUM
# ── N (nouns) ──
noble ADJ
nobody PRON
no DET
noisier ADJ
noisiest ADJ
noisy ADJ
nonetheless CONJ
no one PRON
noon N
nope INTJ
nor CONJ
normal ADJ
normally ADV
north ADV
northern N
nose N
notebook N
notebooks N
nothing PRON
noticed V
noticeed V
noticeing V
notices V
notice V
noticing V
notifyed V
notifying V
notifys V
notify V
notwithstanding PREP
now CONJ
nowhere PRON
now that CONJ
nuclear ADJ
number N
numbers N
numerous ADJ
# ── NUM (numbers) ──
nurse N
nyanza N
object N
objects N
observeed V
observeing V
observes V
observe V
obviously INTJ
occasional ADJ
occasionally ADV
occured V
occuring V
occurs V
occur V
ocean N
oceans N
odd ADJ
office N
officer N
offices N
official ADJ
officially ADV
off PREP
of PREP
often ADV
oh INTJ
oil N
okay INTJ
ok INTJ
old ADJ
once CONJ
one another PRON
one PRON
ones PRON
only ADV
on PREP
onto PREP
ooh INTJ
oops INTJ
opened V
opening V
openly ADV
opens V
open V
opinion N
opposite PREP
optional ADJ
orange ADJ
or CONJ
ordered V
ordering V
orders V
order V
ordinary ADJ
organization N
organizeed V
organizeing V
organizes V
organize V
original ADJ
other DET
others PRON
otherwise CONJ
ouch INTJ
ought AUX
our DET
ourselves PRON
ours PRON
outdoor ADJ
outer ADJ
out PREP
outside PREP
outward ADV
overall CONJ
over PREP
owl N
owls N
owned V
owner N
owners N
owning V
owns V
own V
paid V
painted V
painter N
painters N
painting V
paints V
paint V
pale ADJ
pants N
paper N
papers N
parallel ADJ
parent N
park N
parks N
parrot N
parrots N
partial ADJ
particularly ADV
partly ADV
part N
parts N
party N
passed V
passing V
passs V
pass V
pasteed V
pasteing V
pastes V
paste V
past PREP
path N
paths N
patient ADJ
pattern N
patterns N
paying V
pays V
pay V
peace N
pebble N
pebbles N
peeked V
peeking V
peeks V
peek V
pencil N
pencils N
pending PREP
penguin N
penguins N
pen N
pens N
people N
perfect ADJ
permanent ADJ
per PREP
persisted V
persisting V
persists V
persist V
personal ADJ
personality N
personally ADV
person N
pet N
pets N
pharmacist N
philosophical ADJ
phone N
phones N
phony ADJ
photographer N
physical ADJ
physically ADV
picked V
picking V
picks V
pick V
piece N
pieces N
pig N
pigs N
pilot N
pink ADJ
pipe N
pipes N
placeed V
placeing V
place N
places V
plain N
plains N
planed V
plane N
planes N
planet N
planets N
planing V
plan N
plans N
planted V
planting V
plant N
plants N
plastic N
plateau N
plateaus N
plate N
plates N
played V
player N
players N
playing V
plays V
play V
pleaded V
pleading V
pleads V
plead V
plenty ADJ
plus PREP
point N
pointy ADJ
pole N
police N
polite ADJ
politer ADJ
politest ADJ
political ADJ
politically ADV
politics N
pond N
ponds N
pool N
pools N
poor ADJ
poorer ADJ
poorest ADJ
port N
ports N
position N
possessed V
possessing V
possesss V
possess V
posted V
posting V
posts V
post V
posy ADJ
poured V
pouring V
pours V
pour V
power N
practical ADJ
practically ADV
practiced V
practiceed V
practiceing V
practices V
practice V
practicing V
praiseed V
praiseing V
praises V
praise V
precisely ADV
prefered V
prefering V
prefers V
prefer V
prepareed V
prepareing V
prepares V
prepare V
# ── PREP (prepositions) ──
present ADJ
presently ADV
president N
pressed V
pressing V
presss V
press V
prevented V
preventing V
prevents V
prevent V
previous ADJ
previously ADV
price N
prices N
pricey ADJ
prickly ADJ
primary ADJ
prince N
princess N
principal N
printed V
printing V
prints V
print V
private ADJ
problem N
problems N
processes N
process N
produced V
produces V
produce V
producing V
professional ADJ
professionally ADV
professor N
programmer N
progress N
project N
projects N
promiseed V
promiseing V
promises V
promise V
# ── PRON (pronouns) ──
protected V
protecting V
protects V
protect V
proud ADJ
provided CONJ
public ADJ
publicly ADV
published V
publisher N
publishing V
publishs V
publish V
puffy ADJ
pulled V
pulling V
pulls V
pull V
punched V
punching V
punchs V
punch V
pupil N
pure ADJ
purely ADV
purer ADJ
purest ADJ
purple ADJ
purpose N
purse N
pushed V
pushes V
pushing V
pushs V
push V
puts V
putted V
putting V
put V
quality N
quantity N
quarter NUM
queen N
questioned V
questioning V
question N
questions N
quick ADJ
quickly ADV
quietly ADV
quite ADV
quits V
quitting V
quit V
rabbit N
rabbits N
raced V
races V
race V
racing V
radio N
radios N
rafiki N
rainbow ADJ
rain V
rain N
range N
rang V
ran V
rapid ADJ
rapidly ADV
rare ADJ
rarely ADV
rather ADV
rather than CONJ
rat N
rats N
raw ADJ
reached V
reaching V
reachs V
reach V
readed V
reader N
readers N
reading V
reads V
read V
realized V
realizeed V
realizeing V
realizes V
realize V
realizing V
really INTJ
reason N
reasons N
recalled V
recalling V
recalls V
recall V
receiveed V
receiveing V
receives V
receive V
recent ADJ
recently ADV
recognized V
recognizeed V
recognizeing V
recognizes V
recognize V
recognizing V
recommended V
recommending V
recommends V
recommend V
rectangular ADJ
red ADJ
reduceed V
reduceing V
reduces V
reduce V
refugee N
refused V
refuseed V
refuseing V
refuses V
refuse V
refusing V
regarding PREP
region N
registration N
regular ADJ
regularly ADV
rejected ADJ
rejecting V
rejects V
reject V
relationship N
relationships N
relative N
relaxed ADJ
releaseed V
releaseing V
releases V
release V
religion N
religious ADJ
relyed V
relying V
relys V
rely V
remained V
remaining V
remains V
remain V
remembered V
remembering V
remembers V
remember V
reminded V
reminding V
reminds V
remind V
remote ADJ
removed V
removeed V
removeing V
removes V
remove V
removing V
repeatedly ADV
repeated V
repeating V
repeats V
repeat V
replyed V
replying V
replys V
reply V
reported V
reporter N
reporting V
reports V
report V
represented V
representing V
represents V
represent V
requested V
requesting V
requests V
request V
required V
requireed V
requireing V
requires V
require V
requiring V
rescueed V
rescueing V
rescues V
rescue V
researched V
researching V
researchs V
research V
resideed V
resideing V
resides V
reside V
responded V
responding V
responds V
respond V
restaurant N
restaurants N
rested V
resting V
restricted V
restricting V
restricts V
restrict V
rests V
rest V
resulted V
resulting V
results V
result V
returned V
returning V
returns V
return V
revealed V
revealing V
reveals V
reveal V
reviewed V
reviewing V
reviews V
review V
rib N
ribs N
rice N
rich ADJ
richer ADJ
richest ADJ
ridden V
rided V
rides V
ride V
riding V
rift N
right INTJ
ringing V
ring N
rings V
ripe ADJ
riper ADJ
ripest ADJ
risen V
rises V
rise V
rising V
river N
rivers N
road N
roads N
rock N
rode V
roof N
roofs N
roomy ADJ
rooster N
roosters N
root N
roots N
rope N
ropes N
rose V
rosy ADJ
roughly ADV
round ADJ
rowed V
rowing V
rows V
row V
rude ADJ
ruder ADJ
rudest ADJ
runed V
rung V
runing V
runned V
runner N
runners N
running V
runs V
run V
rural ADJ
rushed V
rushing V
rushs V
rush V
rusty ADJ
sad ADJ
sadder ADJ
saddest ADJ
sadness N
safari N
safe ADJ
safer ADJ
safest ADJ
said V
sailed V
sailing V
sailor N
sails V
sail V
salad N
salmon ADJ
salt N
sand N
sang V
sassy ADJ
sat V
savannah N
savanna N
saveed V
saveing V
saves V
save V
sawa N
saw V
saying V
says V
say V
scanty ADJ
scarier ADJ
scariest ADJ
scarlet ADJ
scary ADJ
school N
schools N
science N
scientific ADJ
scientifically ADV
scientist N
screen N
screens N
sealed V
seal N
seals N
sea N
searched V
searching V
searchs V
search V
seas N
secondary ADJ
second N
seconds N
secretly ADV
seed N
seeds N
seeing V
seemed V
seeming V
seems V
seem V
seen V
sees V
see V
seldom ADV
selfish ADJ
selling V
sells V
sell V
semester N
sended V
sending V
sends V
send V
senseed V
senseing V
senses V
sense V
sentence N
sentences N
sent V
separateed V
separateing V
separates V
separate V
serious ADJ
seriously INTJ
sets V
setting V
set V
seven NUM
seventeen NUM
seventh NUM
seventy NUM
several DET
shadow N
shaked V
shaken V
shakes V
shake V
shaking V
shall AUX
shallow ADJ
shallower ADJ
shallowest ADJ
shamba N
shape N
shapes N
shareed V
shareing V
shares V
share V
shark N
sharks N
sharp ADJ
sharply ADV
sheep N
she PRON
shines V
shine V
shining V
shiny ADJ
ship N
ships N
shirt N
shirts N
shoes N
shone V
shook V
shooting V
shoots V
shoot V
shop N
shops N
shore N
shores N
short ADJ
shorter ADJ
shortest ADJ
shot V
should AUX
shoulder N
shoulders N
shouldnt AUX
shouted V
shouting V
shouts V
shout V
showed V
showing V
show N
shown V
shows V
show V
shuts V
shutting V
shut V
sick ADJ
side N
sides N
sideways ADV
significantly ADV
sign N
signs N
silly ADJ
silver ADJ
similarities N
similarity N
simple ADJ
simply INTJ
since CONJ
singed V
singer N
singers N
singing V
single ADJ
sings V
sing V
sister N
sited V
siting V
sits V
sitted V
sitting V
situation N
situations N
sit V
six NUM
sixteen NUM
sixth NUM
sixty NUM
size N
skill N
skin N
skinny ADJ
skiped V
skiping V
skips V
skip V
skull N
sky N
sleeping V
sleeps V
sleep V
slept V
sliced V
slices V
slice V
slicing V
slides V
slide V
sliding V
slid V
slim ADJ
slimmer ADJ
slimmest ADJ
slow ADV
slowly ADV
small ADJ
smaller ADJ
smallest ADJ
smart ADJ
smelled V
smelling V
smells V
smell V
smileed V
smileing V
smiles V
smile V
smoke N
smoothly ADV
snack N
snacks N
snake N
snakes N
snow N
social ADJ
socially ADV
society N
so CONJ
sofa N
sofas N
soft ADJ
softer ADJ
softest ADJ
softly ADV
soil N
soldier N
soldiers N
sold V
solid ADJ
solution N
solutions N
solveed V
solveing V
solves V
solve V
somali N
somebody PRON
some DET
someone PRON
something PRON
sometimes ADV
somewhere PRON
son N
soon ADV
so that CONJ
soup N
south ADV
spare ADJ
sparkly ADJ
sparrow N
sparrows N
spat V
speaked V
speaker N
speakers N
speaking V
speaks V
speak V
special ADJ
specialist N
specific ADJ
speed N
spended V
spending V
spends V
spend V
spent V
spice N
spices N
spicy ADJ
spider N
spiders N
spine N
spits V
spitting V
spit V
splited V
spliting V
splits V
splitting V
split V
spoken V
spoke V
spoon N
spoons N
spoted V
spoting V
spots V
spot V
sprang V
spreading V
spreads V
spread V
springs V
spring V
sprinted V
sprinting V
sprints V
sprint V
sprung V
square ADJ
squeezeed V
squeezeing V
squeezes V
squeeze V
squirrel N
squirrels N
stable ADJ
stadium N
stadiums N
staff N
stage N
stages N
stairs N
stale ADJ
standing V
stands V
stand V
stareed V
stareing V
stares V
stare V
star N
stars N
started V
starting V
starts V
start V
stated V
state N
states N
stating V
station N
stations N
stayed V
staying V
stays V
stay V
stealing V
steals V
stealthy ADJ
steal V
steamy ADJ
steel N
step N
steps N
still ADV
stinging V
stings V
sting V
stired V
stiring V
stirs V
stir V
stolen V
stole V
stomach N
stone N
stones N
stony ADJ
stood V
stoped V
stoping V
stopped V
stopping V
stops V
stop V
store N
stores N
storm N
stormy ADJ
story N
straight ADJ
strange ADJ
stranger N
stream N
streams N
street N
streets N
strength N
stressed ADJ
strikes V
strike V
striking V
strolled V
strolling V
strolls V
stroll V
strongly ADV
struck V
structure N
structures N
student N
students N
studied V
studies V
studyed V
studying V
studys V
study V
stuffy ADJ
stung V
style N
succeeded V
succeeding V
succeeds V
succeed V
success N
such DET
such that CONJ
sudden ADJ
suddenly ADV
sugar N
suggested V
suggesting V
suggests V
suggest V
suitable ADJ
suit N
sukuma N
sung V
sun N
sunrise N
sunset N
supported V
supporter N
supporting V
supports V
support V
supposed V
supposes V
suppose V
supposing V
sure INTJ
surface N
surfaces N
surgeon N
surly ADJ
surprised ADJ
surprisingly ADV
survivor N
suspect N
swahili N
swamp N
swamps N
swam V
sweeping V
sweeps V
sweep V
swept V
swift ADJ
swimed V
swiming V
swimmer N
swimmers N
swimming V
swims V
swim V
swinging V
swings V
swing V
switches N
switch N
sword N
swords N
swum V
swung V
symbol N
symbols N
system N
systems N
table N
tables N
tablet N
tablets N
# Tags: DET N V ADJ ADV PREP PRON CONJ AUX NUM PROPER_N INTJ
taked V
taken V
takes V
take V
taking V
talked V
talking V
talks V
talk V
tall ADJ
taller ADJ
tallest ADJ
tasted V
tasteed V
tasteing V
tastes V
taste V
tastier ADJ
tastiest ADJ
tasting V
tasty ADJ
taught V
teached V
teacher N
teachers N
teaches V
teaching V
teachs V
teach V
teal ADJ
team N
tea N
technical ADJ
technically ADV
technology N
teenager N
teen N
teeth N
television N
telling V
tells V
tell V
temperature N
temple N
temples N
temporary ADJ
ten NUM
tenth NUM
terrible ADJ
tested V
testing V
tests V
test V
text N
texts N
than CONJ
thanked V
thankfully INTJ
thanking V
thanks V
thank V
that DET
that PRON
the DET
their DET
theirs PRON
them PRON
themselves PRON
then ADV
theoretical ADJ
theoretically ADV
therapist N
there ADV
thereby CONJ
therefore CONJ
thereof CONJ
these DET
thesis N
they PRON
thick ADJ
thicker ADJ
thickest ADJ
thika N
thin ADJ
thing N
things N
thinking V
thinks V
think V
thinner ADJ
thinnest ADJ
third NUM
thirteen NUM
thirty NUM
this DET
thorny ADJ
those DET
though CONJ
thoughts N
thought V
thousand NUM
three NUM
threw V
throat N
throughout PREP
through PREP
throwing V
thrown V
throws V
throw V
thumb N
thumbs N
thunder N
thus CONJ
ticked V
ticking V
ticks V
tick V
tide N
tides N
tiger N
tigers N
tightly ADV
tighty ADJ
time N
times N
tiny ADJ
tired ADJ
titan PROPER_N
toad N
toads N
toasty ADJ
today ADV
toe N
toes N
together ADV
told V
tomorrow ADV
tomorrow N
tongue N
tonight ADV
too ADV
took V
tool N
tools N
tooth N
top ADJ
to PREP
total ADJ
totally ADV
touched V
touches V
touching V
touchs V
touch V
tough ADJ
tougher ADJ
toughest ADJ
tourist N
toward PREP
towards PREP
toy N
toys N
tradeed V
tradeing V
trades V
trade V
traditional ADJ
tradition N
trained V
trainer N
training V
trains V
train V
transformed V
transforming V
transforms V
transform V
transparent ADJ
traveled V
traveler N
traveling V
travels V
travel V
tree N
trees N
triangular ADJ
trickier ADJ
trickiest ADJ
tricky ADJ
trillion NUM
tripped V
tripping V
trips V
trip V
truck N
trucks N
truly ADV
trusted V
trusting V
trusts V
trust V
truth N
turkana N
turkey N
turkeys N
turned V
turning V
turns V
turn V
turquoise ADJ
turtle N
turtles N
tv N
twelfth NUM
twelve NUM
twenty NUM
twice NUM
two NUM
typeed V
typeing V
type N
types V
typical ADJ
typically ADV
ugali N
ugh INTJ
uglier ADJ
ugliest ADJ
ugly ADJ
uhuru N
uncle N
underground ADJ
underneath PREP
under PREP
understanding V
understands V
understand V
understood V
unfortunately INTJ
uniform N
unique ADJ
universal ADJ
university N
# Unknown/new words (names, places, slang) default to N at runtime.
unless CONJ
unlike PREP
until CONJ
unto PREP
unusual ADJ
updateed V
updateing V
updates V
update V
upon PREP
up PREP
u PRON
upstairs ADV
urban ADJ
used V
uses V
use V
using V
us PRON
usually ADV
valid ADJ
valley N
valleys N
value N
values N
van N
vans N
various ADJ
vast ADJ
vegetable N
vegetables N
vein N
veins N
versus PREP
vertical ADJ
very ADV
via PREP
victim N
viewed V
viewing V
view N
views V
villain N
violent ADJ
violet ADJ
visited V
visiting V
visitor N
visitors N
visits V
visit V
volcanoes N
volcano N
volunteer N
voters N
vs PREP
# ── V (verbs) ──
waited V
waiting V
waits V
wait V
wakes V
wake V
waking V
walked V
walking V
walks V
walk V
wallet N
wall N
walls N
wandered V
wandering V
wanders V
wander V
wanted V
wanting V
wants V
want V
warm ADJ
warmer ADJ
warmest ADJ
war N
warned V
warning V
warns V
warn V
was AUX
washed V
washing V
washs V
wash V
wasnt AUX
watched V
watching V
watch N
watchs V
watered V
waterfall N
waterfalls N
watering V
water N
waters V
wave N
waves N
wavy ADJ
weakly ADV
weakness N
wealthy ADJ
weapon N
weapons N
weared V
wearing V
wears V
wear V
weather N
weekly ADV
week N
weeks N
weeping V
weeps V
weep V
weight N
weird ADJ
welcomeed V
welcomeing V
welcomes V
welcome V
well INTJ
went V
we PRON
wept V
were AUX
werent AUX
west ADV
western N
wet ADJ
wetter ADJ
wettest ADJ
whale N
whales N
whatever PRON
what PRON
when CONJ
whenever CONJ
whereas CONJ
whereby CONJ
where CONJ
wherein CONJ
wherever CONJ
whether CONJ
whichever PRON
which PRON
while CONJ
whispered V
whispering V
whispers V
whisper V
white ADJ
whoa INTJ
whoever PRON
whole ADJ
whomever PRON
whom PRON
who PRON
whose PRON
whosever DET
why ADV
wide ADJ
widely ADV
wider ADJ
widest ADJ
width N
wife N
wildlife N
will AUX
wind N
window N
windows N
wine N
winner N
winning V
wins V
win V
wire N
wires N
wisdom N
wise ADJ
wiser ADJ
wisest ADJ
wished V
wishing V
wishs V
wish V
within PREP
without PREP
with PREP
witness N
woken V
woke V
wolf N
wolves N
woman N
women N
wondered V
wonderful ADJ
wondering V
wonders V
wonder V
wont AUX
won V
wood N
woolly ADJ
word N
words N
wore V
worked V
worker N
workers N
working V
works V
work V
world N
worldwide ADV
worm N
worms N
wormy ADJ
worn V
worried ADJ
worries V
worrying V
worry V
worse ADJ
worst ADJ
worth PREP
worthy ADJ
would AUX
wouldnt AUX
wow INTJ
wrinkly ADJ
wrist N
wrists N
writeed V
writeing V
writer N
writers N
writes V
write V
writing V
written V
wrong N
wrote V
yay INTJ
yeah INTJ
yearly ADV
year N
years N
yellow ADJ
yep INTJ
yesterday ADV
yet CONJ
young ADJ
you PRON
your DET
yourself PRON
yourselves PRON
yours PRON
zebra N
zebras N
zero DET
zone N
downloading V
do V
does V
did V
done V
doing V
correctly ADV
hasnt AUX
wont AUX
building N
rain N
attack N
titan PROPER_N
watch N
show N
although CONJ
however CONJ
before CONJ
after CONJ
if CONJ
because CONJ
exams N
circumstance N
sets V
sun N
keys N
missing ADJ
empty ADJ
room N
correctly ADV
homework N
late ADJ
late ADV
were AUX
did AUX
done V
did V
do V
# New vocabulary for 48 sentences
because CONJ
although CONJ
while CONJ
when CONJ
after CONJ
if CONJ
then CONJ
but CONJ
and CONJ
or CONJ
that CONJ
who PRON
which PRON
girl N
reads V
apple N
playing V
football N
tall ADJ
quickly ADV
house N
intelligent ADJ
student N
problem N
easily ADV
under PREP
table N
barking V
loudly ADV
placed V
glass N
wooden ADJ
shelf N
beard N
walks V
slowly ADV
tired ADJ
continued V
working V
attended V
meeting N
explained V
lesson N
listened V
carefully ADV
later ADV
gave V
trusted V
saw V
barked V
met V
smiled V
told V
sister N
study V
harder ADV
sitting V
near PREP
window N
uncle N
yesterday ADV
recommended V
interesting ADJ
solved V
brilliant ADJ
person N
built V
chased V
mouse N
stole V
cheese N
wearing V
shirt N
black ADJ
shoes N
field N
friends N
shouting V
weather N
extremely ADV
cold ADJ
roads N
covered V
ice N
driver N
journey N
important ADJ
decided V
retire V
realized V
spend V
family N
software N
engineer N
designed V
system N
processes V
user N
requests N
real ADJ
time N
works V
conference N
forgot V
submit V
assignment N
week N
tried V
situation N
refused V
accept V
excuse N
Visiting V
relatives N
annoying ADJ
telescope N
Flying V
planes N
dangerous ADJ
ready ADJ
eat V
women N
quietly ADV
market N
bought V
apples N
oranges N
bananas N
grapes N
stores V
names N
addresses N
phone N
numbers N
email N
accounts N
likes V
reading V
watching V
movies N
games N
manager N
hired V
engineers N
designers N
analysts N
highly ADV
skilled ADJ
said V
passes V
taught V
proud ADJ
developer N
wrote V
code N
fixed V
bug N
harder ADJ
expected V
leads V
team N
builds V
application N
arrives V
start V
scientist N
discovered V
method N
improves V
performance N
applied V
neighbor N
principal N
praised V
ceremony N
company N
recently ADV
registered V
platform N
daily ADV
extremely ADV
material N
complex ADJ
understand V
short ADJ
dog N
dogs N
cat N
cats N
chase V
chases V
chased V
chaseing V
solve V
solves V
solved V
solveing V
dog V
dogs V

```

## File: `docs/AGENT.md`

```markdown
# AGENT.md — English Parse Tree Compiler

**Current phase:** Phase 1

---

## 1. Project Identity

**What this is:** A C++17 command-line tool that accepts an English sentence or arithmetic expression and produces:
1. A labelled parse tree (rendered as ASCII art)
2. A symbol table listing every word with its POS tag, grammar role, and scope
3. A declaration of which parsing strategy was used (Top-Down or Bottom-Up)

**What this is NOT:**
- A full NLP pipeline (no semantics, no coreference, no ML)
- A general-purpose English grammar (handles a defined, finite CFG only)
- A web app, GUI, or interactive REPL (stdout only)

---

## 2. Non-Negotiable Rules

- **Never allocate raw `ParseNode*` outside of `std::unique_ptr`** — the tree owns all nodes via `unique_ptr`. If a parse attempt fails, the unique_ptr destructor cleans up automatically.
- **Never modify the token vector after lexing** — the parser reads from a `const std::vector<Token>&`. This prevents cursor/iterator invalidation bugs.
- **Always print the parsing strategy label before the tree** — output order: strategy → tree → symbol table.
- **Backtracking must save and restore the exact cursor value** — never assume a `parse_*()` call has no side effects on the cursor when it fails.
- **Grammar rules must match exactly the symbols defined in `pos_dict.h`** — a mismatch (e.g., matching "VERB" when your enum is `POS::V`) will silently fail every reduction.
- **The symbol table must be built post-parse** — do not build it during parsing (the tree may be discarded on backtrack). Always traverse the final accepted tree.

---

## 3. What NOT To Do

- **Do not use `dynamic_cast` or RTTI** — all node types are handled via the `NodeType` enum field and string label. Keep it simple.
- **Do not share ParseNode ownership across trees** — each parse attempt creates its own tree. Don't `std::move` a node into two different parents.
- **Do not add a POS tag for a word class you don't handle in grammar rules** — if you add `POS::INTERJECTION` to the dict, you must also handle it in the parser or it becomes a dead token that breaks parsing.
- **Do not hardcode display widths** — column widths in the symbol table must compute dynamically from the max length of each column's data.
- **Do not conflate `label` and `lexeme`** — internal nodes (NP, VP, S) have a `label` only. Leaf nodes have both a `label` (POS tag) and a `lexeme` (the actual word).
- **Do not try to parse sentences that don't fit the grammar silently** — always emit a clear error message: `"Error: Could not parse input as a valid sentence or expression."`.

---

## 4. Phase Task Checklists

### Phase 1 — Project Setup & POS Dictionary
**Goal:** Compilable skeleton + working POS tagger.

- [ ] Create directory structure: `include/`, `src/`, `tests/`, `tests/fixtures/`
- [ ] Write `CMakeLists.txt` with main executable and test target
- [ ] Define `POS` enum in `include/pos_dict.h`:
      `{ DET, N, V, ADJ, ADV, PREP, PRON, CONJ, AUX, NUM, PROPER_N, UNKNOWN }`
- [ ] Implement `pos_dict.cpp`: populate `unordered_map<string, POS>` with at least 80 common English words (20 nouns, 20 verbs, 10 determiners, 10 adjectives, 10 adverbs, 10 prepositions)
- [ ] Implement suffix heuristic in `Lexer::assign_pos()`:
      `-ing` → V, `-ly` → ADV, `-ed` → V, `-tion/-ness/-ment` → N
- [ ] Write `Lexer::split_words()`: split on spaces + strip punctuation `.,:;!?`
- [ ] Write `Lexer::tokenize()`: calls `split_words()` then `assign_pos()` per word
- [ ] Implement `Token` struct with `word`, `tag`, `position`
- [ ] Write `tests/test_lexer.cpp` with at least 10 test cases
- [ ] Verify: `./english-parser "The dog runs"` prints token stream to stdout (temporary debug output)

**Phase 1 complete when:** `cmake --build . && ./run_tests` passes all lexer tests with zero failures.

---

### Phase 2 — Parse Tree Data Structure + Display
**Goal:** Build, traverse, and render the parse tree before any parsing logic.

- [ ] Define `NodeType` enum: `{ TERMINAL, NON_TERMINAL }`
- [ ] Implement `ParseNode` struct in `include/parse_tree.h`
- [ ] Implement `ParseNode::add_child(unique_ptr<ParseNode>)` in `src/parse_tree.cpp`
- [ ] Implement `Display::print_node()` — recursive, with prefix string:
      - If child is last: use `"└── "`; else use `"├── "`
      - Propagate `"│   "` vs `"    "` for deeper levels
- [ ] Implement `Display::print_tree(const ParseNode* root)` — calls `print_node(root, "", true)`
- [ ] Manually construct a test tree and call `print_tree()` on it (hardcoded, no parsing yet)
- [ ] Verify expected output for a 3-level tree:
```
S
├── NP
│   ├── DET: "The"
│   └── N: "dog"
└── VP
    └── V: "runs"
```
- [ ] Write `tests/test_display.cpp` that captures stdout and compares to expected string

**Phase 2 complete when:** Hardcoded tree renders with correct ASCII connectors; no `│` lines misaligned.

---

### Phase 3 — Top-Down Parser (Recursive Descent)
**Goal:** Parse English sentences using recursive descent; produce correct parse trees.

- [ ] Implement `TopDownParser` class in `include/top_down_parser.h` + `src/top_down_parser.cpp`
- [ ] Implement `cursor_` management: `current()`, `peek(int)`, `at_end()`, `consume(POS)`
- [ ] Implement `parse_S()`:
      try `NP VP`, then `NP VP PP`; return first success or `nullptr`
- [ ] Implement `parse_NP()`:
      try rules in order: `DET ADJ ADJ N` → `DET ADJ N` → `DET N` → `PRON` → `N`
      use saved cursor + backtracking for each attempt
- [ ] Implement `parse_VP()`:
      try: `V NP PP` → `V NP` → `V PP` → `V ADV` → `V`
- [ ] Implement `parse_PP()`:
      expect `PREP` then `NP`; return `nullptr` if no PREP
- [ ] Wire `TopDownParser::parse()` to try `parse_S()` first, then expression parser
- [ ] Test with fixtures:
      - "The dog runs" → S(NP(DET,N), VP(V))
      - "The quick brown fox jumps over the lazy dog" → full tree
      - "She sees him" → S(NP(PRON), VP(V, NP(PRON)))
- [ ] Print `"Parsing strategy: Top-Down (Recursive Descent)"` before the tree
- [ ] Write `tests/test_top_down.cpp` with at least 8 sentence test cases

**Phase 3 complete when:** All 8 test sentences produce correct tree structures (verified by checking `tree->label`, `tree->children[0]->label`, etc. in tests).

---

### Phase 4 — Bottom-Up Parser (Shift-Reduce)
**Goal:** Alternate parsing mode; produces same parse tree structure via bottom-up strategy.

- [ ] Implement `StackItem` struct: holds `unique_ptr<ParseNode>` + `string symbol`
- [ ] Implement `BottomUpParser` class in `include/bottom_up_parser.h` + `src/bottom_up_parser.cpp`
- [ ] Implement `shift()`: create TERMINAL `ParseNode` for `tokens_[input_pos_]`, push to `stack_`, advance `input_pos_`
- [ ] Implement `stack_top_matches(vector<string> pattern)`: check if top N stack items' symbols match `pattern` (from bottom to top)
- [ ] Implement `reduce_NP()`: check patterns `{"DET","ADJ","N"}`, `{"DET","N"}`, `{"PRON"}`, `{"N"}`; pop + build NP node
- [ ] Implement `reduce_VP()`: check patterns `{"V","NP","PP"}`, `{"V","NP"}`, `{"V","PP"}`, `{"V","ADV"}`, `{"V"}`; pop + build VP node
- [ ] Implement `reduce_PP()`: check pattern `{"PREP","NP"}`; pop + build PP node
- [ ] Implement `reduce_S()`: check pattern `{"NP","VP"}`; pop + build S node
- [ ] Implement `try_reduce()`: call each reduce_*() in priority order (PP first, then NP, VP, S); return `true` if any succeeded
- [ ] Implement main `parse()` loop:
      ```
      while not (stack has one item with symbol "S" AND input exhausted):
          if try_reduce(): continue
          elif not at_end(): shift()
          else: return nullptr  // stuck — parse failure
      ```
- [ ] Implement safeguard: if loop runs > `tokens_.size() * 10` iterations, return `nullptr`
- [ ] Print `"Parsing strategy: Bottom-Up (Shift-Reduce)"` when `--bottom-up` flag is used
- [ ] Write `tests/test_bottom_up.cpp` — same 8 sentences as Phase 3

**Phase 4 complete when:** Bottom-up produces structurally identical trees to top-down for all 8 test sentences.

---

### Phase 5 — Symbol Table
**Goal:** Walk the final parse tree and populate the symbol table.

- [ ] Implement `SymbolEntry` struct: `index`, `lexeme`, `pos_tag`, `grammar_role`, `scope`
- [ ] Implement `SymbolTable::traverse(const ParseNode* node, const string& scope)`:
      - If node is TERMINAL: create `SymbolEntry`, infer `grammar_role` from parent's label + child position
      - If node is `PP`: recurse with `scope = "Prepositional"`
      - Otherwise recurse with current scope
- [ ] Implement `grammar_role` derivation logic:
      - `DET` child of `NP` → `"NP.determiner"`
      - `N` child of `NP` → `"NP.head"`
      - `ADJ` child of `NP` → `"NP.modifier"`
      - `V` child of `VP` → `"VP.head"`
      - `AUX` child of `VP` → `"VP.auxiliary"`
      - `PREP` child of `PP` → `"PP.head"`
      - fallback → `parent_label + "." + pos_tag`
- [ ] Implement `SymbolTable::print()`: render the table with aligned columns
- [ ] Write `tests/test_symbol_table.cpp`:
      - verify entry count matches number of words
      - verify verb entry has `grammar_role == "VP.head"`
      - verify determiner has correct scope

**Phase 5 complete when:** All symbol table tests pass; table renders with consistent column alignment.

---

### Phase 6 — Expression Parser + main() Integration
**Goal:** Handle arithmetic expressions; wire everything together with CLI flags.

- [ ] Implement `detect_input_type(const vector<Token>&)`: returns `InputType::SENTENCE` or `InputType::EXPRESSION`
      - EXPRESSION: first token is NUM, or any token is `+`, `-`, `*`, `/`
- [ ] Implement expression grammar using recursive descent in `TopDownParser`:
      - `parse_EXPR()` → `parse_TERM()` with `+`/`-` operators
      - `parse_TERM()` → `parse_FACTOR()` with `*`/`/` operators
      - `parse_FACTOR()` → NUM or `(` EXPR `)`
- [ ] Update `Lexer::split_words()` to handle operators and multi-digit numbers:
      - accumulate digit characters into one NUM token
      - emit `+`, `-`, `*`, `/`, `(`, `)` as their own tokens
- [ ] Implement `main.cpp`:
      - parse CLI args: `--bottom-up` flag, input string (remaining args joined)
      - call Lexer → Parser (top-down or bottom-up) → SymbolTable → Display
      - exit code `0` on success, `1` on parse failure
- [ ] Final output format for all runs:
```
========================================
 Parsing Strategy: Top-Down (Recursive Descent)
========================================

Parse Tree:
S
├── NP
│   ├── DET: "The"
│   └── N: "dog"
└── VP
    └── V: "runs"

Symbol Table:
┌───────┬──────────┬─────────┬───────────────┬────────────┐
│ Index │ Lexeme   │ POS Tag │ Grammar Role  │ Scope      │
├───────┼──────────┼─────────┼───────────────┼────────────┤
│ 1     │ The      │ DET     │ NP.determiner │ Sentence   │
│ 2     │ dog      │ N       │ NP.head       │ Sentence   │
│ 3     │ runs     │ V       │ VP.head       │ Sentence   │
└───────┴──────────┴─────────┴───────────────┴────────────┘
```
- [ ] Write `tests/fixtures/sentences.txt` with 10 diverse test sentences
- [ ] Smoke test: run all 10 fixtures, confirm no crashes and output looks correct

**Phase 6 complete when:** `./english-parser "The dog runs"` produces the correct full output. `./english-parser --bottom-up "The dog runs"` produces the same tree with different strategy label. `./english-parser "3 + 4 * 2"` produces an expression parse tree.

---

## 5. Code Style Rules

- **Naming:** `snake_case` for variables/functions, `PascalCase` for classes/structs, `SCREAMING_SNAKE` for enum values (e.g. `POS::DET`)
- **Memory:** `std::unique_ptr` for all tree nodes; no raw `new` in parser code
- **Headers:** use `#pragma once`; no circular includes (parse_tree.h must not include lexer.h)
- **Error output:** use `std::cerr` for error messages, `std::cout` for program output
- **Comments:** every non-trivial function gets a one-line `//` doc comment above it explaining its contract

---

## 6. Debugging Decision Tree

| Symptom | Check First | Then Check |
|---------|-------------|------------|
| `parse()` returns nullptr | Print token stream: `for (auto& t : tokens) cout << t.word << ":" << pos_to_str(t.tag) << " ";` | Missing word in dict + no suffix heuristic match → tagged UNKNOWN |
| Infinite loop in bottom-up | `try_reduce()` returning true but not consuming stack items | Reduce function not popping stack before returning true |
| Wrong tree shape | Print cursor value before/after each `parse_*()` call | `consume()` not advancing cursor on match |
| Symbol table has wrong count | Check PP traversal: PP children are not being visited | `scope` param not passed correctly through recursion |
| ASCII tree has misaligned bars | `is_last` computed using `i < children.size() - 1` (off by one) | Use `i == children.size() - 1` |
| Build fails (linking error) | A `.cpp` file not listed in `CMakeLists.txt` | Missing `add_executable` source entry |

---

## 7. Reference Checklist (Before Demo)

- [ ] Top-down parse works for at least 5 diverse sentences
- [ ] Bottom-up parse works for at least 3 sentences
- [ ] Both modes produce structurally identical trees for the same input
- [ ] Symbol table shows correct grammar roles for nouns, verbs, determiners
- [ ] Arithmetic expression parses correctly with correct tree (`EXPR`, `TERM`, `FACTOR`)
- [ ] Unknown words are handled gracefully (not a crash, fallback to heuristic)
- [ ] Parse failure emits a clear error message, not a segfault
- [ ] Strategy label always appears in output

---

## 8. Not In Scope (Ever)

- **Semantic analysis** — no meaning extraction, no WordNet, no entity linking
- **Machine learning POS tagging** — no ML models; dictionary + heuristics only
- **Ambiguity resolution** — when two parses are valid, the first successful parse wins
- **Long-distance dependencies** — no wh-movement, no relative clauses beyond simple PP attachment
- **File input mode** — input is always a single command-line string or stdin line
- **Interactive mode / REPL** — one input → one output → exit

```

## File: `docs/PROJECT_GUIDE.md`

```markdown
# English Parse Tree Compiler — Project Guide

**Language:** C++17  
**Domain:** Compiler Design · Natural Language Processing · Formal Grammar  
**Scope:** Takes an English sentence or arithmetic expression, produces an annotated parse tree (ASCII + structured), a symbol table, and identifies the parsing strategy used (top-down or bottom-up).

---

## Table of Contents
1. [How an English Compiler Works](#1-how-an-english-compiler-works)
2. [Project Structure](#2-project-structure)
3. [Recommended Libraries](#3-recommended-libraries)
4. [Testing Strategy](#4-testing-strategy)
5. [Debugging Decision Tree](#5-debugging-decision-tree)

---

## 1. How an English Compiler Works

### 1.1 Pipeline Overview

A traditional compiler has three front-end stages. This project maps those same stages onto natural language:

```
INPUT (English string)
        │
        ▼
┌───────────────┐
│  LEXER        │  Splits text into tokens (words + punctuation)
│  (Tokenizer)  │  Tags each word with a Part-of-Speech (POS)
└───────┬───────┘
        │  Token stream: [(word, POS), ...]
        ▼
┌───────────────┐
│  PARSER       │  Applies CFG grammar rules
│               │  Builds the parse tree
│               │  Top-Down OR Bottom-Up mode
└───────┬───────┘
        │  ParseTree*
        ▼
┌───────────────┐
│  SYMBOL TABLE │  Extracts nouns, verbs, adjectives into
│  BUILDER      │  a structured lookup table
└───────┬───────┘
        │
        ▼
┌───────────────┐
│  DISPLAY      │  Renders ASCII tree + symbol table to stdout
└───────────────┘
```

### 1.2 Lexical Analysis (Tokenization + POS Tagging)

The lexer does two jobs in one pass:

**Tokenization** — split the input string into words. Handle punctuation by stripping or isolating it.

```
"The quick brown fox jumps over the lazy dog."
→ ["The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"]
```

**POS Tagging** — assign each word a grammatical category. You can implement a simplified rule-based tagger using a dictionary:

| Tag  | Category      | Examples                          |
|------|---------------|-----------------------------------|
| DET  | Determiner    | the, a, an, this, that            |
| N    | Noun          | fox, dog, cat, man, city          |
| V    | Verb          | runs, jumps, eats, is, sees       |
| ADJ  | Adjective     | quick, brown, lazy, tall, happy   |
| ADV  | Adverb        | quickly, slowly, very, soon       |
| PREP | Preposition   | over, under, in, on, at, by, to   |
| PRON | Pronoun       | he, she, it, they, I, you         |
| CONJ | Conjunction   | and, or, but, because, although   |
| AUX  | Auxiliary     | is, was, were, has, have, can     |
| NUM  | Number        | one, two, 42, 3.14                |

Your dictionary is a `std::unordered_map<std::string, POS>`. For unknown words, apply suffix heuristics:
- ends in `-ing` → V (gerund) or ADJ (participial)
- ends in `-ly` → ADV
- ends in `-ed` → V (past tense)
- ends in `-tion`, `-ness`, `-ment` → N
- starts uppercase mid-sentence → PROPER_N

### 1.3 Context-Free Grammar (CFG) for English

Your grammar defines legal sentence structures. This is the ruleset your parser enforces.

**Sentence Grammar:**
```
S   → NP VP
    | NP VP PP

NP  → DET N
    | DET ADJ N
    | DET ADJ ADJ N
    | PRON
    | N
    | PROPER_N

VP  → V
    | AUX V
    | V NP
    | V NP PP
    | V PP
    | V ADV

PP  → PREP NP

ADJ_LIST → ADJ
         | ADJ ADJ_LIST
```

**Expression Grammar (for arithmetic input):**
```
EXPR   → TERM (('+' | '-') TERM)*
TERM   → FACTOR (('*' | '/') FACTOR)*
FACTOR → NUM
       | '(' EXPR ')'
```

> The parser detects whether the input is an English sentence or an arithmetic expression by checking the first token. If it's a number or if the string contains operators (`+`, `-`, `*`, `/`), route to the expression parser; otherwise, route to the sentence parser.

### 1.4 Parse Tree

The parse tree is the central data structure. Each node has:
- A **label** (the grammar symbol: `S`, `NP`, `VP`, `V`, `N`, etc.)
- A **value** (for leaf nodes: the actual word)
- A list of **children**

```cpp
struct ParseNode {
    std::string label;    // "NP", "VP", "V", "the", etc.
    std::string value;    // only set for terminals (leaves)
    bool is_terminal;
    std::vector<std::unique_ptr<ParseNode>> children;
};
```

**ASCII Tree Display** — render the tree to stdout using indentation + connectors:

```
S
├── NP
│   ├── DET: "The"
│   └── N:   "fox"
└── VP
    ├── V:   "jumps"
    └── PP
        ├── PREP: "over"
        └── NP
            ├── DET: "the"
            └── N:   "fence"
```

The rendering algorithm: recursively walk the tree; for each child, print the right prefix (`├──` for non-last children, `└──` for the last child). Thread the vertical bar `│` down through siblings.

### 1.5 Top-Down Parsing (Recursive Descent)

**Strategy:** Start from the start symbol `S`, try to predict which rule to apply based on the next token (lookahead), and recurse down.

```
parseS()  →  calls parseNP(), parseVP()
parseNP() →  looks at current token:
               if DET → apply "DET N" or "DET ADJ N"
               if PRON → apply "PRON"
               else    → try bare N
parseVP() →  looks at current token:
               if V → try V, V NP, V NP PP, V PP, V ADV
```

**Key implementation notes:**
- Maintain a **cursor** (index into token array). Each `parse*()` function advances the cursor as it consumes tokens.
- Use **backtracking** when multiple rules could apply: save cursor position, try a rule, if it fails restore cursor and try the next.
- This is **LL(1)** parsing — one token of lookahead. Most English sentences are unambiguous at this level.
- Return `nullptr` on failure, a valid `ParseNode*` on success.

**When to use:** This is the default mode. Label your output with `"Parsing strategy: Top-Down (Recursive Descent)"`.

### 1.6 Bottom-Up Parsing (Shift-Reduce)

**Strategy:** Start with individual tokens, apply grammar rules in reverse to reduce groups of tokens into non-terminals, working up to `S`.

Two operations on a **stack**:
- **SHIFT** — push the next input token onto the stack
- **REDUCE** — pop the top N items from the stack that match the RHS of a rule, push the LHS

```
Input: "The fox jumps"
Stack: []

SHIFT "The"  → Stack: [The/DET]
SHIFT "fox"  → Stack: [The/DET, fox/N]
REDUCE NP → DET N  → Stack: [NP]
SHIFT "jumps" → Stack: [NP, jumps/V]
REDUCE VP → V  → Stack: [NP, VP]
REDUCE S → NP VP  → Stack: [S]  ✓ ACCEPT
```

**Key implementation notes:**
- Implement the stack as `std::vector<StackItem>` where each `StackItem` holds a `ParseNode*` plus its grammar symbol.
- The parser table (what to shift vs reduce) can be a simple hand-coded priority: always try to reduce before shifting if a valid reduction exists.
- This is an **LR(0)** style parser — simpler than full LR(1) but sufficient for the grammar defined above.
- When you successfully reduce, build the `ParseNode`: create a new non-terminal node, attach the popped nodes as children.
- Label your output with `"Parsing strategy: Bottom-Up (Shift-Reduce)"`.

**When to use:** Offer this as a `--bottom-up` flag. Or switch automatically when the input is an arithmetic expression.

### 1.7 Symbol Table

The symbol table records all meaningful words found in the input. It is built from the completed parse tree (not during parsing — post-pass).

```
┌──────────────────────────────────────────────────────────────────┐
│                        SYMBOL TABLE                              │
├────────┬──────────┬──────────┬────────────────┬─────────────────┤
│ Index  │ Lexeme   │ POS Tag  │ Grammar Role   │ Scope           │
├────────┼──────────┼──────────┼────────────────┼─────────────────┤
│ 1      │ The      │ DET      │ NP.determiner  │ Sentence        │
│ 2      │ fox      │ N        │ NP.head        │ Sentence        │
│ 3      │ jumps    │ V        │ VP.head        │ Sentence        │
│ 4      │ over     │ PREP     │ PP.head        │ Prepositional   │
│ 5      │ the      │ DET      │ NP.determiner  │ Prepositional   │
│ 6      │ fence    │ N        │ NP.head        │ Prepositional   │
└────────┴──────────┴──────────┴────────────────┴─────────────────┘
```

Implement as `std::vector<SymbolEntry>` where each entry has: index, lexeme, pos_tag, grammar_role, scope.

The "Grammar Role" is derived by traversing the parse tree and noting which node each terminal falls under. For example, a noun that is the direct child of `NP` has role `NP.head`; a verb that is the direct child of `VP` has role `VP.head`.

### 1.8 Runtime Flow

```
User Input
    │
    ▼
main()
    │── detect_input_type() ──► "sentence" or "expression"
    │
    ├── [sentence] ──► Lexer::tokenize(input)
    │                     │
    │                     ▼ token stream
    │               Parser::parse_top_down()  OR  Parser::parse_bottom_up()
    │                     │
    │                     ▼ ParseTree root
    │               SymbolTableBuilder::build(root)
    │                     │
    │                     ▼ SymbolTable
    │               Display::print_tree(root)
    │               Display::print_symbol_table(table)
    │               Display::print_strategy("Top-Down" | "Bottom-Up")
    │
    └── [expression] ──► same flow, expression grammar
```

---

## 2. Project Structure

```
english-parser/
├── CMakeLists.txt           # Build config
├── README.md
├── AGENT.md
├── ROADMAP.md
│
├── include/
│   ├── lexer.h              # Tokenizer + POS tagger declarations
│   ├── parser.h             # Base Parser class
│   ├── top_down_parser.h    # Recursive descent parser
│   ├── bottom_up_parser.h   # Shift-reduce parser
│   ├── parse_tree.h         # ParseNode + ParseTree structs
│   ├── symbol_table.h       # SymbolEntry + SymbolTable
│   ├── display.h            # ASCII tree + table rendering
│   └── pos_dict.h           # POS dictionary + heuristics
│
├── src/
│   ├── main.cpp             # Entry point, argument handling
│   ├── lexer.cpp            # Tokenizer implementation
│   ├── pos_dict.cpp         # Dictionary data + suffix rules
│   ├── top_down_parser.cpp  # Recursive descent parse*() functions
│   ├── bottom_up_parser.cpp # Shift-reduce stack machine
│   ├── parse_tree.cpp       # Node construction, tree traversal
│   ├── symbol_table.cpp     # Post-parse tree walk, table building
│   └── display.cpp          # Rendering logic
│
└── tests/
    ├── test_lexer.cpp        # POS tagging unit tests
    ├── test_top_down.cpp     # Parse tree correctness for known sentences
    ├── test_bottom_up.cpp    # Shift-reduce correctness
    ├── test_symbol_table.cpp # Symbol table extraction
    └── fixtures/
        ├── sentences.txt     # Sample inputs (one per line)
        └── expected/         # Expected tree output (for diff testing)
```

### Module Mini-Specs

**`lexer.h / lexer.cpp`**
```cpp
struct Token {
    std::string word;
    POS         tag;
    int         position;   // 0-indexed position in input
};

class Lexer {
public:
    explicit Lexer(const std::string& input);
    std::vector<Token> tokenize();       // main entry point
private:
    std::vector<std::string> split_words(const std::string& s);
    POS assign_pos(const std::string& word);
};
```

**`parse_tree.h`**
```cpp
enum class NodeType { TERMINAL, NON_TERMINAL };

struct ParseNode {
    std::string label;                              // "NP", "VP", "N", etc.
    std::string lexeme;                             // only for terminals
    NodeType    type;
    std::vector<std::unique_ptr<ParseNode>> children;

    void add_child(std::unique_ptr<ParseNode> child);
    bool is_leaf() const { return type == NodeType::TERMINAL; }
};
```

**`top_down_parser.h`**
```cpp
class TopDownParser {
public:
    explicit TopDownParser(std::vector<Token> tokens);
    std::unique_ptr<ParseNode> parse();    // returns root or nullptr on failure

private:
    std::vector<Token>  tokens_;
    size_t              cursor_;

    std::unique_ptr<ParseNode> parse_S();
    std::unique_ptr<ParseNode> parse_NP();
    std::unique_ptr<ParseNode> parse_VP();
    std::unique_ptr<ParseNode> parse_PP();
    std::unique_ptr<ParseNode> parse_ADJ_list();

    Token& current();
    Token& peek(int offset = 0);
    bool   consume(POS expected, ParseNode* parent);
    bool   at_end() const;
};
```

**`bottom_up_parser.h`**
```cpp
struct StackItem {
    std::unique_ptr<ParseNode> node;
    std::string symbol;   // the grammar symbol this node represents
};

class BottomUpParser {
public:
    explicit BottomUpParser(std::vector<Token> tokens);
    std::unique_ptr<ParseNode> parse();

private:
    std::vector<Token>    tokens_;
    size_t                input_pos_;
    std::vector<StackItem> stack_;

    void   shift();
    bool   try_reduce();
    bool   reduce_NP();
    bool   reduce_VP();
    bool   reduce_PP();
    bool   reduce_S();
    bool   stack_top_matches(std::vector<std::string> pattern);
};
```

**`symbol_table.h`**
```cpp
struct SymbolEntry {
    int         index;
    std::string lexeme;
    std::string pos_tag;        // "N", "V", "DET", etc.
    std::string grammar_role;   // "NP.head", "VP.head", etc.
    std::string scope;          // "Sentence", "Prepositional", etc.
};

class SymbolTable {
public:
    void build(const ParseNode* root);
    void print() const;
    const std::vector<SymbolEntry>& entries() const;

private:
    std::vector<SymbolEntry> entries_;
    int counter_ = 1;
    void traverse(const ParseNode* node, const std::string& scope);
};
```

**`display.h`**
```cpp
class Display {
public:
    static void print_tree(const ParseNode* root);
    static void print_symbol_table(const SymbolTable& table);
    static void print_strategy(const std::string& name);

private:
    static void print_node(const ParseNode* node,
                           const std::string& prefix,
                           bool is_last);
};
```

---

## 3. Recommended Libraries

This project is intentionally self-contained. No heavy NLP frameworks are needed. All dependencies should be available via your system package manager or CMake FetchContent.

| Library      | Version  | Purpose                          | Install              |
|--------------|----------|----------------------------------|----------------------|
| Google Test  | 1.14.0   | Unit testing framework           | CMake FetchContent   |
| tabulate     | 1.5      | Pretty table printing (optional) | CMake FetchContent   |

> For the symbol table display, you can use `tabulate` (header-only C++ library) for clean aligned columns, or implement your own printf-based column padding — the latter is simpler for a university project.

**CMake FetchContent for GoogleTest:**
```cmake
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)
```

**CMakeLists.txt skeleton:**
```cmake
cmake_minimum_required(VERSION 3.20)
project(EnglishParser CXX)
set(CMAKE_CXX_STANDARD 17)

# Main executable
add_executable(english-parser
    src/main.cpp
    src/lexer.cpp
    src/pos_dict.cpp
    src/top_down_parser.cpp
    src/bottom_up_parser.cpp
    src/parse_tree.cpp
    src/symbol_table.cpp
    src/display.cpp
)
target_include_directories(english-parser PRIVATE include)

# Tests
enable_testing()
# ... FetchContent GoogleTest ...
add_executable(run_tests
    tests/test_lexer.cpp
    tests/test_top_down.cpp
    tests/test_bottom_up.cpp
    tests/test_symbol_table.cpp
    src/lexer.cpp
    src/pos_dict.cpp
    src/top_down_parser.cpp
    src/bottom_up_parser.cpp
    src/parse_tree.cpp
    src/symbol_table.cpp
    src/display.cpp
)
target_include_directories(run_tests PRIVATE include)
target_link_libraries(run_tests GTest::gtest_main)
```

---

## 4. Testing Strategy

### Layer 1: Lexer / POS Tagger Unit Tests

Test individual word tagging:
```cpp
TEST(LexerTest, Determiners) {
    Lexer l("the");
    auto tokens = l.tokenize();
    EXPECT_EQ(tokens[0].tag, POS::DET);
}
TEST(LexerTest, SuffixHeuristic_ly) {
    Lexer l("quickly");
    auto tokens = l.tokenize();
    EXPECT_EQ(tokens[0].tag, POS::ADV);
}
```

### Layer 2: Parser Unit Tests

For each grammar rule, write one sentence that should parse and one that should not:
```cpp
TEST(TopDownTest, SimpleSentence) {
    // "The cat sat" → S → NP VP
    auto tree = parse("The cat sat");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[1]->label, "VP");
}
TEST(TopDownTest, FailsOnNonsense) {
    auto tree = parse("jumps the the");
    EXPECT_EQ(tree, nullptr);
}
```

### Layer 3: Symbol Table Tests

Given a known parse tree, verify symbol table entries:
```cpp
TEST(SymbolTableTest, ExtractsVerb) {
    auto tree = parse("The dog runs");
    SymbolTable st;
    st.build(tree.get());
    auto& entries = st.entries();
    auto verb_it = std::find_if(entries.begin(), entries.end(),
        [](auto& e){ return e.pos_tag == "V"; });
    EXPECT_NE(verb_it, entries.end());
    EXPECT_EQ(verb_it->lexeme, "runs");
    EXPECT_EQ(verb_it->grammar_role, "VP.head");
}
```

### Layer 4: End-to-End / Fixture Tests

Run the full binary against sample sentences and diff the output against golden files:
```bash
# In tests/fixtures/
./english-parser "The quick brown fox jumps over the lazy dog" > out.txt
diff out.txt tests/fixtures/expected/quick_fox.txt
```

---

## 5. Debugging Decision Tree

| Symptom | Likely Cause | Fix |
|---------|-------------|-----|
| `parse()` returns `nullptr` for a valid sentence | POS tagger wrong-tagged a word (e.g. "runs" tagged as N instead of V) | Print token stream before parsing; check `pos_dict.cpp` |
| Parse tree has wrong depth (extra nesting or missing levels) | A `parse_NP()` consumed too many tokens; cursor advanced past correct boundary | Add `cursor_` print before/after each `parse_*()` call |
| Shift-reduce parser loops indefinitely | `try_reduce()` always returns true even with no match, causing infinite loop | Check that `try_reduce()` returns `false` when no pattern matches |
| Bottom-up stack doesn't reach S | A grammar rule pattern is incorrect (wrong symbol names) | Print the stack state after each shift/reduce step |
| Symbol table has missing entries | Tree traversal skips a subtree (e.g. PP children not visited) | Add `assert(node != nullptr)` at start of `traverse()`; trace the tree |
| ASCII tree renders with wrong connectors | `is_last` flag computed incorrectly; off-by-one in children index | Print `children.size()` and the current child index explicitly |
| Unknown words all get the same wrong POS | Suffix heuristic isn't being reached; dictionary lookup short-circuits | Check that unknown-word path (not in dict) falls through to suffix rules |
| Expression parser fails on multi-digit numbers | Tokenizer splits `42` into `4` and `2` (character-by-character) | Tokenizer must use `isdigit()` loop to accumulate full number tokens |
| Segfault on `children[i]` access | `unique_ptr` child was moved out of the tree mid-traversal | Never `std::move` children after tree is built; use `const ParseNode*` in traversal |
| Ambiguous sentence produces wrong parse | Backtracking not restoring cursor correctly | Save `size_t saved = cursor_` before trying alternative; restore on failure |

```

## File: `docs/ROADMAP.md`

```markdown
# ROADMAP — English Parse Tree Compiler

**Project:** C++ compiler for English sentences & arithmetic expressions  
**Output:** Parse tree (ASCII) + symbol table + parsing strategy label  
**Language:** C++17

---

## Phases Overview

| Phase | Name                        | Est. Time | Status      |
|-------|-----------------------------|-----------|-------------|
| 1     | Project Setup + POS Dict    | 1–2 days  | ⬜ Not started |
| 2     | Parse Tree + Display        | 1 day     | ⬜ Not started |
| 3     | Top-Down Parser             | 2–3 days  | ⬜ Not started |
| 4     | Bottom-Up Parser            | 2 days    | ⬜ Not started |
| 5     | Symbol Table                | 1 day     | ⬜ Not started |
| 6     | Expression Parser + main()  | 1–2 days  | ⬜ Not started |

**Total estimated time:** 8–11 days

---

## Phase 1 — Project Setup & POS Dictionary

**Goal:** Compilable project skeleton with a working lexer that correctly tags English words.

**In scope:**
- CMakeLists.txt (builds main executable + test binary)
- `POS` enum definition
- POS dictionary (80+ words minimum)
- Suffix heuristics for unknown words
- Lexer that splits and tags a sentence
- Unit tests for the lexer

**Out of scope:**
- Any parsing logic (no grammar rules yet)
- Parse tree data structures
- Display or output formatting

**Success criteria:**
- `cmake -B build && cmake --build build` succeeds with zero warnings
- `./build/run_tests` passes all lexer tests
- `Lexer("The quick brown fox").tokenize()` returns 4 tokens with correct tags: `[DET, ADJ, ADJ, N]`

**Key implementation notes:**
- Build the dictionary as a `static const unordered_map` in `pos_dict.cpp` — not rebuilt per Lexer instance
- Lowercase the input word before dictionary lookup so "The" and "the" both match
- The suffix rules must run only if the dictionary lookup misses — don't suffix-match known words

---

## Phase 2 — Parse Tree Data Structure & Display

**Goal:** A working ASCII tree renderer before any parsing exists.

**In scope:**
- `ParseNode` struct with `label`, `lexeme`, `type`, `children`
- `Display::print_tree()` — recursive ASCII renderer with `├──`, `└──`, `│` connectors
- Manual tree construction in a test to verify rendering

**Out of scope:**
- Any parser (trees are hand-built in tests for now)
- Symbol table

**Success criteria:**
- A manually constructed tree for "The dog runs" renders exactly as:
```
S
├── NP
│   ├── DET: "The"
│   └── N: "dog"
└── VP
    └── V: "runs"
```
- No missing `│` lines, no extra spaces, correct last-child detection

**Key implementation notes:**
- The rendering prefix must be built incrementally: pass `prefix` string into recursion, appending `"│   "` for non-last children and `"    "` for last children
- `is_last` is `true` when the current child is `children[children.size() - 1]`
- Terminal nodes print as `TAG: "word"`, non-terminals print as just `TAG`

---

## Phase 3 — Top-Down Parser (Recursive Descent)

**Goal:** Parse English sentences using recursive descent; produce correct labelled parse trees.

**In scope:**
- `TopDownParser` class
- Grammar rules for `S`, `NP`, `VP`, `PP` (per CFG in PROJECT_GUIDE.md)
- Backtracking via cursor save/restore
- Printing `"Parsing Strategy: Top-Down (Recursive Descent)"` before output
- Tests for 8 diverse sentences

**Out of scope:**
- Bottom-up parsing
- Expression parsing (numeric input)
- Symbol table
- `main.cpp` integration (can test via direct instantiation)

**Success criteria:**
- `parse("The dog runs")` → tree with `S → NP(DET, N) → VP(V)`
- `parse("The quick brown fox jumps over the lazy dog")` → full nested tree
- `parse("She loves him")` → `S → NP(PRON) → VP(V, NP(PRON))`
- `parse("jumps the the")` → `nullptr` (graceful failure)
- 8 test cases all pass

**Key implementation notes:**
- Try the longest rule first (e.g. `DET ADJ ADJ N` before `DET ADJ N`) to avoid partial matches
- Each `parse_*()` function must restore `cursor_` to its entry value on failure before returning `nullptr`
- `consume(POS tag)` should: check `current().tag == tag`, if yes create a TERMINAL node, advance cursor, return true; if no return false without advancing

---

## Phase 4 — Bottom-Up Parser (Shift-Reduce)

**Goal:** Alternate parsing mode producing the same tree structure via shift-reduce.

**In scope:**
- `BottomUpParser` class with `stack_`, `shift()`, `try_reduce()`
- Reduce functions for each non-terminal: `reduce_NP()`, `reduce_VP()`, `reduce_PP()`, `reduce_S()`
- Infinite-loop safeguard
- `--bottom-up` flag wired in (even if `main()` is minimal at this stage)
- Tests: same 8 sentences as Phase 3

**Out of scope:**
- Full `main()` integration (that's Phase 6)
- Expression parsing

**Success criteria:**
- `BottomUpParser("The dog runs").parse()` returns a tree structurally identical to the top-down result
- `reduce_NP()` correctly matches all 4 NP patterns
- Loop terminates on all 8 test sentences (no infinite loop)
- Parse failure returns `nullptr`, not a crash

**Key implementation notes:**
- Reduction priority matters: try PP before NP, NP before VP, VP before S — otherwise `PREP NP` may be reduced as bare NP
- `stack_top_matches(pattern)` must check from top of stack downward (i.e., pattern is listed left-to-right but the stack top is the rightmost element)
- When building the reduce node, children must be added in left-to-right order (pop stack in reverse, reverse again before adding children)

---

## Phase 5 — Symbol Table

**Goal:** Post-parse tree walk produces a complete, formatted symbol table.

**In scope:**
- `SymbolEntry` struct
- `SymbolTable::build(root)` — walks parse tree, creates entries for all terminals
- `grammar_role` derivation from parent–child relationships
- Scope propagation (`"Sentence"` at top level, `"Prepositional"` under PP)
- `SymbolTable::print()` — aligned column display
- Unit tests

**Out of scope:**
- Semantic roles (not subject/object — just grammar roles like NP.head, VP.head)
- Any modification of the parse tree

**Success criteria:**
- For "The dog runs": 3 entries — `The/DET/NP.determiner`, `dog/N/NP.head`, `runs/V/VP.head`
- For "jumps over the fence": PP children have scope `"Prepositional"`
- Column widths in the table adjust to longest value in each column (no hardcoded widths)

**Key implementation notes:**
- Build the symbol table by passing a `parent_label` down through the recursion — the terminal node itself doesn't know its parent without this
- For determining column widths, do two passes: first collect all entries, then compute `max(lexeme.size())` per column, then render

---

## Phase 6 — Expression Parser + main() Integration

**Goal:** Handle arithmetic expressions; full CLI integration; polished output.

**In scope:**
- `detect_input_type()` — sentence vs expression detection
- Expression grammar added to `TopDownParser`: `EXPR`, `TERM`, `FACTOR`
- Lexer updates: multi-digit numbers, operator tokens
- `main.cpp`: arg parsing, routing, full output pipeline
- Final output format with separators and headers
- Smoke tests against 10 fixture sentences

**Out of scope:**
- Expression evaluation (only parsing/tree, not computation)
- Interactive mode
- File input

**Success criteria:**
- `./english-parser "The dog runs"` → full correct output (strategy + tree + table)
- `./english-parser --bottom-up "The dog runs"` → same tree, different strategy label
- `./english-parser "3 + 4 * 2"` → expression tree showing operator precedence:
```
EXPR
├── TERM
│   └── FACTOR
│       └── NUM: "3"
├── OP: "+"
└── TERM
    ├── FACTOR
    │   └── NUM: "4"
    ├── OP: "*"
    └── FACTOR
        └── NUM: "2"
```
- Unknown/unparseable input prints: `"Error: Could not parse input."` to stderr
- Exit code is `0` on success, `1` on failure

**Key implementation notes:**
- `detect_input_type`: scan token list for any `NUM` token or operator character — if found, it's an expression
- Arithmetic lexer must accumulate digits: `while (isdigit(input[i])) token += input[i++]`
- Operator precedence is encoded in the grammar structure itself (TERM handles `*/`, EXPR handles `+-`) — do not implement an operator precedence table separately

---

## Not In Scope (Ever)

| Feature | Reason |
|---------|--------|
| ML/statistical POS tagger | Requires training data and an ML runtime; far out of scope for a compiler design course |
| Semantic role labeling | This is NLP beyond parsing — the project is about parse trees, not meaning |
| Relative clauses / subordinate clauses | "The man who runs" would require a more complex grammar; deliberately excluded to keep CFG manageable |
| Interactive REPL / `--watch` mode | One-shot input/output only; a loop would complicate error handling with no added learning value |
| Pretty HTML/graphical output | ASCII is sufficient and avoids a rendering dependency; if needed, add as an optional post-Phase-6 extension |
| Full English grammar coverage | The defined CFG handles the most common sentence structures; handling all of English grammar is an open research problem |
| Expression evaluation | Parse tree construction is the goal; evaluating the result is a separate concern (interpreter design) |

```

## File: `docs/addendum-functions-and-ambiguity.md`

```markdown
# English Parser — Addendum: Numerical Functions & Ambiguity Detection

This is an addendum to `PROJECT_GUIDE.md`, `AGENT.md`, and `ROADMAP.md`.
Implement Phase 7 (Numerical Functions) and Phase 8 (Ambiguity Detection)
after Phase 6 is complete.

---

## Table of Contents
1. [How Numerical Functions Work](#1-how-numerical-functions-work)
2. [How Ambiguity Detection Works](#2-how-ambiguity-detection-works)
3. [Updated Data Structures](#3-updated-data-structures)
4. [Updated Grammar Rules](#4-updated-grammar-rules)
5. [Ambiguity: What to Show the User](#5-ambiguity-what-to-show-the-user)
6. [Debugging Notes](#6-debugging-notes)
7. [AGENT.md Additions — Phase 7 & 8 Checklists](#7-agentmd-additions)
8. [ROADMAP.md Additions — Phase 7 & 8](#8-roadmapmd-additions)

---

## 1. How Numerical Functions Work

### 1.1 What counts as a "numerical function"

A numerical function is a named operation applied to one or more numeric arguments:

| Function      | Arity | Example input           |
|---------------|-------|-------------------------|
| `sin`         | 1     | `sin(45)`               |
| `cos`         | 1     | `cos(90)`               |
| `tan`         | 1     | `tan(30)`               |
| `sqrt`        | 1     | `sqrt(16)`              |
| `log`         | 1     | `log(100)`              |
| `log2`        | 1     | `log2(8)`               |
| `abs`         | 1     | `abs(-5)`               |
| `floor`       | 1     | `floor(3.7)`            |
| `ceil`        | 1     | `ceil(3.2)`             |
| `pow`         | 2     | `pow(2, 8)`             |
| `max`         | 2+    | `max(3, 7, 12)`         |
| `min`         | 2+    | `min(3, 7, 12)`         |
| `mod`         | 2     | `mod(10, 3)`            |

Functions can be nested: `sqrt(pow(3, 2) + pow(4, 2))` — this must parse correctly because `EXPR` is reused inside the argument list.

### 1.2 Lexer Changes

Add `POS::FUNC` to the `POS` enum (or a separate `TokenType::FUNC`). In `pos_dict.cpp`, register all function names:

```cpp
// In the numeric token detection section of Lexer::tokenize():
static const std::unordered_set<std::string> MATH_FUNCS = {
    "sin","cos","tan","sqrt","log","log2","abs","floor","ceil",
    "pow","max","min","mod","exp","round"
};

// During tokenization, after reading an alphabetic run:
if (MATH_FUNCS.count(word_lower)) tag = POS::FUNC;
```

Also add tokens for `,` (COMMA) and for `(`, `)` (already needed for expressions). Update `Lexer::split_words()` to emit `(`, `)`, `,` as their own tokens.

### 1.3 Grammar Extension

Extend the expression grammar with function calls and argument lists:

```
EXPR     → TERM (('+' | '-') TERM)*

TERM     → FACTOR (('*' | '/') FACTOR)*

FACTOR   → NUM
          | '(' EXPR ')'
          | FUNC '(' ARGLIST ')'      ← NEW
          | '-' FACTOR                ← unary minus (NEW)

ARGLIST  → EXPR (',' EXPR)*           ← NEW
```

This naturally handles nesting because `ARGLIST` is defined in terms of `EXPR`, which loops back to `FACTOR`, which can again be a `FUNC` call.

### 1.4 Parse Tree Shape for Functions

```
Input: pow(2, 8)

EXPR
└── TERM
    └── FACTOR
        └── FUNC_CALL
            ├── FUNC: "pow"
            └── ARGLIST
                ├── EXPR
                │   └── TERM
                │       └── FACTOR
                │           └── NUM: "2"
                └── EXPR
                    └── TERM
                        └── FACTOR
                            └── NUM: "8"
```

```
Input: sqrt(pow(3, 2) + pow(4, 2))

EXPR
└── TERM
    └── FACTOR
        └── FUNC_CALL
            ├── FUNC: "sqrt"
            └── ARGLIST
                └── EXPR
                    ├── TERM
                    │   └── FACTOR
                    │       └── FUNC_CALL
                    │           ├── FUNC: "pow"
                    │           └── ARGLIST
                    │               ├── EXPR → NUM: "3"
                    │               └── EXPR → NUM: "2"
                    ├── OP: "+"
                    └── TERM
                        └── FACTOR
                            └── FUNC_CALL
                                ├── FUNC: "pow"
                                └── ARGLIST
                                    ├── EXPR → NUM: "4"
                                    └── EXPR → NUM: "2"
```

### 1.5 detect_input_type() Update

The existing check (any NUM or operator → EXPRESSION) must now also trigger on FUNC tokens:

```cpp
InputType detect_input_type(const std::vector<Token>& tokens) {
    for (auto& t : tokens) {
        if (t.tag == POS::NUM || t.tag == POS::FUNC ||
            t.word == "+" || t.word == "-" ||
            t.word == "*" || t.word == "/") {
            return InputType::EXPRESSION;
        }
    }
    return InputType::SENTENCE;
}
```

### 1.6 Symbol Table for Numerical Functions

Add a new grammar role `"FUNC_CALL.name"` for the function name token and `"FUNC_CALL.arg[N]"` for each argument:

```
┌───────┬──────────┬─────────┬──────────────────┬────────────┐
│ Index │ Lexeme   │ POS Tag │ Grammar Role     │ Scope      │
├───────┼──────────┼─────────┼──────────────────┼────────────┤
│ 1     │ pow      │ FUNC    │ FUNC_CALL.name   │ Expression │
│ 2     │ 2        │ NUM     │ FUNC_CALL.arg[0] │ Expression │
│ 3     │ 8        │ NUM     │ FUNC_CALL.arg[1] │ Expression │
└───────┴──────────┴─────────┴──────────────────┴────────────┘
```

---

## 2. How Ambiguity Detection Works

### 2.1 What ambiguity means in this context

A parse is **ambiguous** when two or more distinct parse trees can be produced from the same input under the same grammar. A parse is **unambiguous** when exactly one valid tree exists.

**English ambiguity types you must detect:**

| Type | Example | Ambiguity |
|------|---------|-----------|
| PP attachment | "I saw the man with the telescope" | Did I use the telescope, or does the man have it? |
| ADJ scope | "old men and women" | Are only the men old, or both men and women? |
| V/N ambiguity | "flies like an arrow" | Is "flies" a verb or "like" a verb? |
| Reduced relative | "The horse raced past the barn fell" | Garden-path; two possible tree structures |

**Expression ambiguity** does not occur in your grammar because operator precedence is encoded structurally (`TERM` handles `*/`, `EXPR` handles `+-`). If you see `3 + 4 * 2`, the grammar forces the correct tree. Mark all arithmetic and function expressions as **Unambiguous** automatically.

### 2.2 How to find all parses (exhaustive search)

Change the parser's return type from `unique_ptr<ParseNode>` to `vector<unique_ptr<ParseNode>>`. The parser no longer returns at the first success — it collects all successes.

**Top-down exhaustive parse:**

Each `parse_*()` function returns a `vector` of alternative subtrees instead of one:

```cpp
// Before (returns first match):
std::unique_ptr<ParseNode> parse_NP() {
    if (auto n = try_rule_DET_ADJ_N()) return n;
    if (auto n = try_rule_DET_N())     return n;
    ...
    return nullptr;
}

// After (returns ALL matches):
std::vector<AltResult> parse_NP_all(size_t cursor) {
    std::vector<AltResult> results;
    // try DET ADJ N
    auto [node1, end1] = try_rule_DET_ADJ_N(cursor);
    if (node1) results.push_back({std::move(node1), end1});
    // try DET N
    auto [node2, end2] = try_rule_DET_N(cursor);
    if (node2) results.push_back({std::move(node2), end2});
    // ... etc
    return results;
}
```

`AltResult` is a small struct: `{ unique_ptr<ParseNode> tree; size_t end_cursor; }`.

**PP attachment is the main source of ambiguity.** When parsing `VP`, both of these are valid:

```
"I saw the man with the telescope"

Tree A:                          Tree B:
S                                S
├── NP: "I"                      ├── NP: "I"
└── VP                           └── VP
    ├── V: "saw"                     ├── V: "saw"
    ├── NP: "the man"                └── NP
    └── PP: "with the telescope"         ├── DET: "the"
                                         ├── N: "man"
                                         └── PP: "with the telescope"
```

In Tree A, the PP attaches to the VP (I used the telescope).
In Tree B, the PP attaches to the NP inside the VP (the man has the telescope).

To produce both trees, `parse_VP_all()` must try both:
1. `V NP PP` (PP attaches to VP — Tree A)
2. `V NP` where NP is parsed by `parse_NP_all()` which itself can produce `DET N PP` (PP attaches to NP — Tree B)

### 2.3 Counting and Reporting

After collecting all parse trees, report the result:

```
count == 0  → Parse failure: "Error: Could not parse input."
count == 1  → "Verdict: UNAMBIGUOUS (1 valid parse)"
count >= 2  → "Verdict: AMBIGUOUS (N possible parses)"
```

When ambiguous, display **all trees** numbered:

```
========================================
 Parsing Strategy: Top-Down (Recursive Descent)
 Verdict: AMBIGUOUS (2 possible parses)
========================================

--- Parse Tree 1 of 2 ---
S
├── NP: "I"
└── VP
    ├── V: "saw"
    ├── NP
    │   ├── DET: "the"
    │   └── N: "man"
    └── PP
        ├── PREP: "with"
        └── NP
            ├── DET: "the"
            └── N: "telescope"

  Interpretation: "I used the telescope to see the man"

--- Parse Tree 2 of 2 ---
S
├── NP: "I"
└── VP
    ├── V: "saw"
    └── NP
        ├── DET: "the"
        ├── N: "man"
        └── PP
            ├── PREP: "with"
            └── NP
                ├── DET: "the"
                └── N: "telescope"

  Interpretation: "The man has the telescope"
```

The "Interpretation" line is a hardcoded string derived from which PP attachment rule fired — you don't need NLP to generate it; you detect the structure and pick from a small set of template strings.

### 2.4 Ambiguity Interpretation Template Strings

Derive the interpretation by inspecting the tree structure after parsing:

```cpp
std::string derive_interpretation(const ParseNode* root) {
    // Check: does VP have a PP child directly?
    auto* vp = find_child(root, "VP");
    if (!vp) return "";
    bool pp_in_vp = has_direct_child(vp, "PP");
    bool pp_in_np = false;
    auto* np = find_direct_child(vp, "NP");
    if (np) pp_in_np = has_direct_child(np, "PP");

    if (pp_in_vp)  return "Interpretation: The prepositional phrase modifies the verb (VP attachment)";
    if (pp_in_np)  return "Interpretation: The prepositional phrase modifies the object noun (NP attachment)";
    return "";
}
```

---

## 3. Updated Data Structures

### 3.1 POS Enum additions

```cpp
enum class POS {
    DET, N, V, ADJ, ADV, PREP, PRON, CONJ, AUX, NUM,
    PROPER_N, FUNC,   // ← NEW: math function name
    COMMA, LPAREN, RPAREN,  // ← NEW: punctuation tokens
    UNKNOWN
};
```

### 3.2 AltResult struct (new)

```cpp
struct AltResult {
    std::unique_ptr<ParseNode> tree;
    size_t end_cursor;  // where this parse ended in the token stream
};
```

### 3.3 Parser return type change

```cpp
// Old (single parse):
class TopDownParser {
    std::unique_ptr<ParseNode> parse();
    ...
};

// New (all parses):
class TopDownParser {
    std::vector<std::unique_ptr<ParseNode>> parse_all();  // returns all trees
    std::unique_ptr<ParseNode> parse();                   // returns first, for compat
    ...
private:
    std::vector<AltResult> parse_S_all(size_t cursor);
    std::vector<AltResult> parse_NP_all(size_t cursor);
    std::vector<AltResult> parse_VP_all(size_t cursor);
    std::vector<AltResult> parse_PP_all(size_t cursor);
};
```

The original `parse()` calls `parse_all()` and returns `std::move(results[0].tree)` — backward compatible.

### 3.4 AmbiguityResult struct (new)

```cpp
struct AmbiguityResult {
    std::vector<std::unique_ptr<ParseNode>> trees;
    bool is_ambiguous() const { return trees.size() > 1; }
    bool failed()       const { return trees.empty(); }
};
```

### 3.5 FUNC_CALL node (new parse tree label)

Add `"FUNC_CALL"` and `"ARGLIST"` as valid non-terminal labels. No code change needed — these are just string values for `ParseNode::label`.

---

## 4. Updated Grammar Rules

### 4.1 Full expression grammar (replaces Phase 6 version)

```
EXPR      → TERM (('+' | '-') TERM)*

TERM      → FACTOR (('*' | '/') FACTOR)*

FACTOR    → NUM
           | '(' EXPR ')'
           | FUNC '(' ARGLIST ')'
           | '-' FACTOR

ARGLIST   → EXPR (',' EXPR)*
```

### 4.2 English grammar (extended for ambiguity collection)

```
S      → NP VP
       | NP VP PP          ← produces VP-level PP attachment (one of two trees)

NP     → DET N             ← plain NP
       | DET ADJ N
       | DET ADJ ADJ N
       | DET N PP          ← NP with embedded PP (produces NP-level PP attachment)
       | PRON
       | N

VP     → V
       | V NP              ← NP may itself contain a PP → ambiguity source
       | V NP PP           ← explicit VP-level PP
       | V PP
       | V ADV
       | AUX V
```

The key insight: **both `S → NP VP PP` and `NP → DET N PP` produce grammatically valid trees for the same input**. Your exhaustive parser will find both.

---

## 5. Ambiguity: What to Show the User

### Unambiguous sentence
```
========================================
 Parsing Strategy: Top-Down (Recursive Descent)
 Verdict: UNAMBIGUOUS — exactly 1 valid parse
========================================

Parse Tree:
S
├── NP
│   ├── DET: "The"
│   └── N: "dog"
└── VP
    └── V: "runs"

Symbol Table:
...
```

### Ambiguous sentence
```
========================================
 Parsing Strategy: Top-Down (Recursive Descent)
 Verdict: AMBIGUOUS — 2 possible parses detected
========================================

--- Parse 1 of 2 ---
[tree 1]
Interpretation: The prepositional phrase modifies the verb (VP attachment)

--- Parse 2 of 2 ---
[tree 2]
Interpretation: The prepositional phrase modifies the object noun (NP attachment)

Symbol Table (based on Parse 1):
...
Note: Symbol table roles differ between parses — shown for Parse 1 only.
```

### Failed parse
```
Error: Could not parse input as a valid sentence or expression.
Input: "foxes the over"
Tip: Check that the sentence follows Subject-Verb or Subject-Verb-Object order.
```

### Numerical function (always unambiguous)
```
========================================
 Parsing Strategy: Top-Down (Recursive Descent)
 Input type: Arithmetic / Numerical Expression
 Verdict: UNAMBIGUOUS (operator precedence enforced by grammar)
========================================

Parse Tree:
EXPR
└── ...
```

---

## 6. Debugging Notes

| Symptom | Cause | Fix |
|---------|-------|-----|
| `parse_all()` returns only 1 tree for known ambiguous sentence | `parse_VP_all()` stops after first match | Each rule attempt must push to `results` independently, not early-return |
| Duplicate trees (same structure returned twice) | Two grammar rules produce identical trees for the same token span | After collecting all `AltResult`, deduplicate by comparing tree structure (label + children recursively) |
| `FUNC` token not recognized | Function name in input is uppercase; dict lookup case-sensitive | Lowercase before lookup in `assign_pos()` |
| `parse_ARGLIST()` fails on `pow(2, 8)` | Comma not tokenized as a separate token | Update `Lexer::split_words()` to emit `,` as its own COMMA token |
| Nested function parse fails | `parse_FACTOR()` doesn't recurse into `EXPR` for function args | `parse_ARGLIST()` calls `parse_EXPR_all()` — confirm it's not calling `parse_FACTOR_all()` directly |
| All sentences reported as ambiguous | `parse_NP_all()` always returns both `DET N` and `DET N PP` even when no PP exists | `parse_NP_all()` rule `DET N PP` must only add a result when `parse_PP_all()` returns non-empty |

---

## 7. AGENT.md Additions

Copy-paste the following two phase blocks into `AGENT.md` after Phase 6.

---

### Phase 7 — Numerical Functions
**Goal:** Parse named mathematical functions with arguments; produce correct nested trees.

- [ ] Add `POS::FUNC`, `POS::COMMA` to POS enum in `include/pos_dict.h`
- [ ] Add `MATH_FUNCS` unordered_set in `src/lexer.cpp`; tag function names as `POS::FUNC`
- [ ] Update `Lexer::split_words()` to emit `(`, `)`, `,` as single-character tokens
- [ ] Update `detect_input_type()` to return `EXPRESSION` when any token has `POS::FUNC`
- [ ] Implement `parse_FACTOR()` extension: handle `FUNC '(' ARGLIST ')'` case
- [ ] Implement `parse_ARGLIST()`: parse first `EXPR`, then loop consuming `COMMA EXPR` pairs
- [ ] Implement unary minus: `FACTOR → '-' FACTOR` (recursive, handles `abs(-5)`)
- [ ] Add `"FUNC_CALL"` and `"ARGLIST"` as valid non-terminal labels in the display renderer
- [ ] Add grammar roles to symbol table: `"FUNC_CALL.name"` and `"FUNC_CALL.arg[N]"` where N is 0-indexed
- [ ] Test with: `sin(45)`, `pow(2, 8)`, `sqrt(pow(3,2) + pow(4,2))`, `max(1, min(5, 3))`, `abs(-7)`
- [ ] Write `tests/test_functions.cpp` with at least 5 test cases including a nested call

**Phase 7 complete when:** `./english-parser "sqrt(pow(3,2) + pow(4,2))"` produces a correct nested tree and symbol table with `grammar_role == "FUNC_CALL.name"` for `sqrt` and `pow`.

---

### Phase 8 — Ambiguity Detection
**Goal:** Detect and report all valid parse trees for a given input; classify as Ambiguous or Unambiguous.

- [ ] Add `AltResult` struct to `include/parse_tree.h`
- [ ] Add `AmbiguityResult` struct to `include/parse_tree.h`
- [ ] Refactor `TopDownParser::parse_S()`, `parse_NP()`, `parse_VP()`, `parse_PP()` into `_all()` variants returning `vector<AltResult>`
- [ ] Keep original `parse()` as a wrapper calling `parse_all()[0]` — backward compatible with Phase 3–6 tests
- [ ] Add grammar rule `NP → DET N PP` to `parse_NP_all()` — this is the second source of PP attachment
- [ ] Add grammar rule `S → NP VP PP` to `parse_S_all()` — first source of PP attachment
- [ ] Implement deduplication: after collecting all trees, remove structurally identical ones (recursive label+children compare)
- [ ] Implement `derive_interpretation(const ParseNode*)` — template string based on PP attachment site
- [ ] Implement `Display::print_ambiguity_result(const AmbiguityResult&)`:
      - If `failed()`: print error message + tip
      - If `!is_ambiguous()`: print single tree with `"UNAMBIGUOUS"` header
      - If `is_ambiguous()`: print all trees numbered, each with interpretation line
- [ ] Mark all EXPRESSION inputs as UNAMBIGUOUS automatically (skip exhaustive search)
- [ ] Write `tests/test_ambiguity.cpp`:
      - `"The dog runs"` → unambiguous
      - `"I saw the man with the telescope"` → ambiguous (2 trees)
      - `"She ate the cake on the table"` → ambiguous (2 trees)
      - `"He runs"` → unambiguous
      - `"3 + 4 * 2"` → unambiguous (expression)
- [ ] Update `main.cpp` to use `parse_all()` and `AmbiguityResult` instead of single `parse()`

**Phase 8 complete when:** `./english-parser "I saw the man with the telescope"` outputs exactly 2 parse trees with correct interpretation labels and `AMBIGUOUS` verdict.

---

## 8. ROADMAP.md Additions

Copy-paste the following two phase blocks into `ROADMAP.md` after Phase 6.

---

### Phase 7 — Numerical Functions

**Goal:** Extend the expression grammar to handle named mathematical functions with one or more arguments, including nested calls.

**In scope:**
- `POS::FUNC` token type + function name dictionary
- `,` (COMMA) as a distinct token
- Grammar rules: `FACTOR → FUNC '(' ARGLIST ')'`, `ARGLIST → EXPR (',' EXPR)*`
- Unary minus: `FACTOR → '-' FACTOR`
- Symbol table roles: `FUNC_CALL.name`, `FUNC_CALL.arg[N]`
- Tests: 5+ cases including nested function calls

**Out of scope:**
- Evaluating the function (computing `sin(45)` — this is a parser, not a calculator)
- User-defined functions (only built-in names listed in `MATH_FUNCS`)
- Variable/symbol arguments (only numeric `EXPR` as args — no `x`, `y`)

**Success criteria:**
- `sqrt(pow(3,2) + pow(4,2))` produces a correct deeply-nested tree
- Symbol table shows `sqrt` as `FUNC_CALL.name`, `3` as `FUNC_CALL.arg[0]`, `2` as `FUNC_CALL.arg[1]` (inside inner `pow`)
- All Phase 3–6 tests still pass (no regression)

**Key implementation notes:**
- `parse_ARGLIST()` must stop on `)` — check that current token is not `)` before consuming COMMA
- Unary minus binds tighter than binary minus — it's in `FACTOR`, not `EXPR`
- `max(1, 2, 3)` (3 arguments) must work — `ARGLIST` loop handles variable arity

---

### Phase 8 — Ambiguity Detection

**Goal:** Run exhaustive parsing to find all valid parse trees; classify each input as Ambiguous or Unambiguous; display all trees with interpretation hints.

**In scope:**
- `_all()` variants of all parse functions returning `vector<AltResult>`
- Grammar extended with NP-level PP attachment (`NP → DET N PP`)
- Deduplication of structurally identical trees
- `derive_interpretation()` for PP attachment ambiguity
- `AmbiguityResult` struct and updated `Display` output
- Automatic UNAMBIGUOUS classification for all expression inputs
- 5 test cases for ambiguity detection

**Out of scope:**
- Detecting ambiguity types other than PP attachment (e.g. coordination scope, verb/noun homonymy)
- Ranking parses by likelihood (no probability model)
- Bottom-up exhaustive parsing (ambiguity detection applies to top-down mode only)
- Generating natural language explanations beyond the template strings

**Success criteria:**
- `"The dog runs"` → `UNAMBIGUOUS (1 parse)`
- `"I saw the man with the telescope"` → `AMBIGUOUS (2 parses)` with distinct trees
- `"3 + 4 * 2"` → `UNAMBIGUOUS` (expression, auto-classified)
- No duplicate trees reported for any input
- Original `parse()` (single result) still works — all Phase 3–6 tests pass

**Key implementation notes:**
- The deduplication step is essential — without it, some inputs produce 3–4 copies of the same tree from different rule orderings
- Structural comparison: two trees are identical if their labels match and all children are pairwise identical (recursive)
- The `_all()` refactor must pass the cursor by value into each alternative attempt, not by reference — otherwise one attempt's cursor advancement pollutes the next attempt

```

## File: `docs/plan.md`

```markdown
# Dictionary System Plan
## How to make the parser handle any word — including Kenyan names, uni jargon, and slang

---

## The Core Problem (and why a bigger list alone won't fully solve it)

English has ~170,000 active words, but **no dictionary can be complete forever**. New names, slang, technical terms, and proper nouns (Maasai Mara, KU, Strathmore, Matatu, Harambee...) will always appear. The real fix is a **layered system** where the dictionary handles known words, smart heuristics handle patterns, and anything left over defaults safely to **Noun (N)** — because unknown words used in a sentence are almost always acting as nouns.

---

## The 3-Layer Architecture

```
Input word
    │
    ▼
Layer 1: Dictionary Lookup          ← dictionary.txt (3800+ entries, exact match)
    │  Found? → return that POS
    │  Not found?
    ▼
Layer 2: Suffix Heuristics          ← patterns in lexer.cpp
    │  -ing → V      (running, sleeping, building)
    │  -ly  → ADV    (quickly, slowly, beautifully)   [min 4 chars — "fly" is NOT ADV]
    │  -ed  → V      (walked, talked, jumped)
    │  -tion/-ness/-ment → N   (action, happiness, payment)
    │  Uppercase mid-sentence → PROPER_N  (Nairobi, Fawzy, Maasai)
    │  Not matched?
    ▼
Layer 3: Default fallback           ← lexer.cpp
    └── return N                    ← ALWAYS noun for unknown words
```

This means:
- **"Maasai"** → not in dict → uppercase mid-sentence → **PROPER_N** ✓  
- **"matatu"** → not in dict → no suffix match → **N** (treated as noun) ✓  
- **"Strathmore"** → not in dict → uppercase → **PROPER_N** ✓  
- **"ugali"** → not in dict → **N** ✓  
- **"kicking"** → not in dict → ends in -ing → **V** ✓  
- **"governmental"** → not in dict → no suffix match → **N** (acceptable fallback)

---

## Step 1: Replace the hardcoded dictionary in `pos_dict.cpp`

The current `pos_dict.cpp` has a `static const unordered_map` baked into the source code with ~100 words. **Replace the entire file** with the version below that:
1. Loads `data/dictionary.txt` at startup
2. Falls back gracefully if the file is missing
3. Returns `POS::UNKNOWN` for unlisted words (lexer then applies heuristics)

### New `src/pos_dict.cpp`

```cpp
#include "pos_dict.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// Runtime dictionary — populated by load_dictionary()
static std::unordered_map<std::string, POS> DICTIONARY;

std::string pos_to_str(POS tag) {
    switch(tag) {
        case POS::DET:     return "DET";
        case POS::N:       return "N";
        case POS::V:       return "V";
        case POS::ADJ:     return "ADJ";
        case POS::ADV:     return "ADV";
        case POS::PREP:    return "PREP";
        case POS::PRON:    return "PRON";
        case POS::CONJ:    return "CONJ";
        case POS::AUX:     return "AUX";
        case POS::NUM:     return "NUM";
        case POS::PROPER_N:return "PROPER_N";
        case POS::OP:      return "OP";
        case POS::LPAREN:  return "LPAREN";
        case POS::RPAREN:  return "RPAREN";
        case POS::UNKNOWN: return "UNKNOWN";
        default:           return "UNKNOWN";
    }
}

POS str_to_pos(const std::string& s) {
    if (s == "DET")      return POS::DET;
    if (s == "N")        return POS::N;
    if (s == "V")        return POS::V;
    if (s == "ADJ")      return POS::ADJ;
    if (s == "ADV")      return POS::ADV;
    if (s == "PREP")     return POS::PREP;
    if (s == "PRON")     return POS::PRON;
    if (s == "CONJ")     return POS::CONJ;
    if (s == "AUX")      return POS::AUX;
    if (s == "NUM")      return POS::NUM;
    if (s == "PROPER_N") return POS::PROPER_N;
    if (s == "INTJ")     return POS::INTJ;
    return POS::UNKNOWN;
}

void load_dictionary(const std::string& filename) {
    // Seed with minimal fallback so parser works even without the file
    DICTIONARY = {
        {"the",POS::DET},{"a",POS::DET},{"an",POS::DET},
        {"is",POS::AUX},{"are",POS::AUX},{"was",POS::AUX},
        {"he",POS::PRON},{"she",POS::PRON},{"it",POS::PRON},
        {"they",POS::PRON},{"i",POS::PRON},{"you",POS::PRON},
        {"we",POS::PRON},{"him",POS::PRON},{"her",POS::DET},
        {"and",POS::CONJ},{"but",POS::CONJ},{"or",POS::CONJ},
        {"in",POS::PREP},{"on",POS::PREP},{"at",POS::PREP},
        {"to",POS::PREP},{"over",POS::PREP},{"with",POS::PREP},
    };

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: dictionary file '" << filename
                  << "' not found. Parser will use suffix heuristics only.\n";
        return;
    }

    std::string line;
    int loaded = 0;
    while (std::getline(file, line)) {
        // Strip comments (# to end of line)
        auto hash = line.find('#');
        if (hash != std::string::npos) line = line.substr(0, hash);

        std::istringstream iss(line);
        std::string word, tag_str;
        if (!(iss >> word >> tag_str)) continue;

        POS tag = str_to_pos(tag_str);
        if (tag == POS::UNKNOWN) continue;

        // Lowercase all keys — lookup is always case-insensitive
        std::transform(word.begin(), word.end(), word.begin(),
            [](unsigned char c){ return std::tolower(c); });
        DICTIONARY[word] = tag;
        loaded++;
    }
    std::cerr << "Loaded " << loaded << " dictionary entries from " << filename << "\n";
}

POS lookup_word(const std::string& word) {
    auto it = DICTIONARY.find(word);
    return (it != DICTIONARY.end()) ? it->second : POS::UNKNOWN;
}
```

### Updated `src/lexer.cpp` — assign_pos fallback fix

Change the last line of `assign_pos()` from returning `POS::UNKNOWN` to returning `POS::N`:

```cpp
POS Lexer::assign_pos(const std::string& word, bool is_first_word) {
    if (word.empty()) return POS::UNKNOWN;

    // --- operator / numeric tokens ---
    if (word == "+" || word == "-" || word == "*" || word == "/") return POS::OP;
    if (word == "(") return POS::LPAREN;
    if (word == ")") return POS::RPAREN;
    bool all_digits = true;
    for (char c : word) if (!std::isdigit(c)) { all_digits = false; break; }
    if (all_digits) return POS::NUM;

    // --- dictionary lookup (case-insensitive) ---
    std::string lower = word;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    POS tag = lookup_word(lower);
    if (tag != POS::UNKNOWN) return tag;

    // --- suffix heuristics (for words NOT in dictionary) ---
    if (lower.size() > 3 && lower.substr(lower.size()-3) == "ing") return POS::V;
    if (lower.size() >= 4 && lower.substr(lower.size()-2) == "ly")  return POS::ADV;
    if (lower.size() > 2 && lower.substr(lower.size()-2) == "ed")   return POS::V;
    if (lower.size() > 4 &&
       (lower.substr(lower.size()-4) == "tion" ||
        lower.substr(lower.size()-4) == "ness" ||
        lower.substr(lower.size()-4) == "ment"))                    return POS::N;

    // Capitalised mid-sentence → proper noun (Nairobi, Fawzy, Maasai)
    if (!is_first_word && std::isupper(word[0])) return POS::PROPER_N;

    // ── FINAL FALLBACK: unknown words are treated as Nouns ──
    // Names (Wanjiku, Kipchoge, Strathmore), slang (matatu, ugali),
    // technical terms — all work as nouns in a parse tree.
    return POS::N;
}
```

> **The `-ly` fix** on line 4 of the heuristics changes `> 2` to `>= 4`. Without this, the 3-letter word "fly" was matched as ADV (`f-l-y` ends in `ly`). With the fix, only words 4+ characters long get the ADV treatment.

---

## Step 2: Update `main.cpp` to call `load_dictionary()`

Add one line near the top of `main()` before the Lexer is created:

```cpp
int main(int argc, char* argv[]) {
    // ── load dictionary at startup ──
    load_dictionary("data/dictionary.txt");
    // ... rest of main unchanged
```

Make sure `#include "pos_dict.h"` is at the top of `main.cpp` — it likely already is.

---

## Step 3: Place the dictionary file

Put `dictionary.txt` in the `data/` folder of your project:

```
cpp-Project/
├── data/
│   └── dictionary.txt    ← 3800+ entries, this file
├── src/
│   ├── pos_dict.cpp      ← updated (loads from file)
│   ├── lexer.cpp         ← updated (N fallback + -ly fix)
│   └── main.cpp          ← updated (calls load_dictionary)
└── ...
```

Rebuild with:
```bash
g++ -std=c++17 src/*.cpp -Iinclude -o english-parser
./english-parser "The quick brown fox jumps over the lazy dog"
```

---

## Step 4: How to add new words yourself

The dictionary file is plain text — one word per line, format: `word TAG`. Comments start with `#`.

**Example — adding Kenyan/local words:**
```text
# ── Kenyan / local words ──
nairobi N
mombasa N
kisumu N
maasai PROPER_N
kikkikuyu PROPER_N
matatu N
boda N
ugali N
sukuma N
harambee N
safari N
mzungu N
wanjiku PROPER_N
kipchoge PROPER_N
mmu N
strathmore N
kenyatta N
maseno N
egerton N
```

**Example — adding your university's terminology:**
```text
cat N
cat V
cdf N
assignment N
semester N
transcript N
coursework N
elective N
prerequisite N
internship N
dissertation N
```

**Example — fixing a misclassified word:**
If "data" is parsing wrong (it's a plural noun but sometimes used as non-count):
```text
data N
datum N
```

**Rules for adding entries:**
1. One word per line, lowercase
2. Use exactly one tag: `DET N V ADJ ADV PREP PRON CONJ AUX NUM PROPER_N`
3. Lines starting with `#` are comments — use them to organise sections
4. Later entries in the file overwrite earlier ones for the same word
5. Put your custom additions at the **bottom** of the file under `# ── CUSTOM ──`

---

## Step 5: When a word still fails (debugging guide)

If a sentence fails to parse, the problem is almost always a wrong POS tag. Find which word is wrong using this mental checklist:

| Symptom | What to check |
|---------|---------------|
| Parser returns null for `"X verbs"` | Is the verb (e.g. "loves", "drinks") tagged V? Check it's in `dictionary.txt` under V. |
| A noun is being treated as a verb | That word was given V tag in dict. Add it: `wordname N` at bottom of dict. |
| "fly" tagged as ADV | You have the old `> 2` check in `assign_pos`. Change it to `>= 4`. |
| Name like "Nairobi" tagged as N not PROPER_N | It's the first word of the sentence — the uppercase heuristic skips position 0. Add it: `nairobi PROPER_N`. |
| Slang word breaks parse | It's probably UNKNOWN → now defaults to N. If it's acting as a verb (e.g. "vibing"), add `vibing V` to dict. |
| Sentence with "his/her/their" fails NP rule | These are DET in the grammar, not PRON. Both are in the dict as DET. |

---

## Why unknown words default to N (not UNKNOWN)

The parser's grammar rules use POS tags to match tokens. If a word is tagged `UNKNOWN`, no grammar rule ever matches it, and the entire parse fails even if the rest of the sentence is perfect.

Defaulting to `N` means:
- **"Wanjiku runs"** → `PROPER_N V` → parser tries `NP(PROPER_N) VP(V)` → **succeeds** ✓  
- **"The matatu runs"** → `DET N V` → `NP(DET N) VP(V)` → **succeeds** ✓  
- **"Harambee builds communities"** → `N V N` → `NP(N) VP(V NP(N))` → **succeeds** ✓  
- **"jabberwocky"** → `N` → can serve as subject or object ✓

The only case where this fails is if an unknown word is *actually* functioning as a verb, adjective, or preposition in the sentence. In practice, proper names and new nouns appear far more frequently than unknown verbs (which almost always have recognisable -ing/-ed suffixes anyway).

---

## Dictionary Coverage Summary

The generated `dictionary.txt` contains **3,812 entries** covering:

| POS Tag | Count | What's covered |
|---------|-------|----------------|
| V       | 1,689 | ~400 verbs × base/3ps/past/pp/ing forms; all irregular verbs explicit |
| N       | 1,056 | People, body, animals, nature, objects, abstract, African/Kenyan terms |
| ADJ     | 547   | Size, color, emotion, temporal, spatial, academic/technical |
| ADV     | 160   | Degree, frequency, time, place, manner |
| PRON    | 57    | All personal, demonstrative, relative, indefinite pronouns |
| DET     | 38    | Articles, possessives, quantifiers |
| PREP    | 67    | All English prepositions |
| CONJ    | 64    | Coordinating + subordinating conjunctions |
| AUX     | 44    | All modal + be/have/do forms |
| NUM     | 44    | Number words (one–trillion, ordinals) |
| INTJ    | 46    | Interjections (oh, wow, hey, etc.) |

**What it doesn't cover** (handled by fallback):
- Archaic or highly specialised vocabulary
- Proper nouns (people's names, place names) → PROPER_N via uppercase heuristic
- New slang / Swahili / local words → N via default fallback
- Novel compound words → N via default fallback

```

## File: `include/bottom_up_parser.h`

```c
#pragma once
#include "lexer.h"
#include "parse_tree.h"
#include <vector>
#include <memory>
#include <string>

struct StackItem {
    std::unique_ptr<ParseNode> node;
    std::string symbol;
};

class BottomUpParser {
public:
    explicit BottomUpParser(const std::vector<Token>& tokens);
    std::unique_ptr<ParseNode> parse();

private:
    std::vector<Token> tokens_;
    size_t input_pos_;
    std::vector<StackItem> stack_;

    void shift();
    bool try_reduce();
    bool reduce_NP();
    bool reduce_VP();
    bool reduce_PP();
    bool reduce_S();
    
    bool stack_top_matches(const std::vector<std::string>& pattern) const;
    bool at_end() const;
};

```

## File: `include/display.h`

```c
#pragma once
#include "parse_tree.h"
#include "symbol_table.h"
#include <string>
#include <vector>

class Display {
public:
    static void print_tree(const ParseNode* root);
    static void print_strategy(const std::string& name);
    static void print_symbol_table(const SymbolTable& table);
    static void export_dot(const ParseNode* root, const std::string& filename);

private:
    static std::vector<std::string> render_tree_2d(const ParseNode* node);
    static void export_dot_node(const ParseNode* node, int& id_counter, std::ofstream& out);
};

```

## File: `include/lexer.h`

```c
#pragma once
#include "pos_dict.h"
#include <string>
#include <vector>

struct Token {
    std::string word;
    POS tag;
    int position;
};

class Lexer {
public:
    explicit Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string input_;
    std::vector<std::string> split_words(const std::string& s);
    POS assign_pos(const std::string& word, bool is_first_word);
};

```

## File: `include/parse_tree.h`

```c
#pragma once
#include <string>
#include <vector>
#include <memory>

enum class NodeType { TERMINAL, NON_TERMINAL };

struct ParseNode {
    std::string label;
    std::string lexeme;
    NodeType type;
    std::vector<std::unique_ptr<ParseNode>> children;

    void add_child(std::unique_ptr<ParseNode> child);
    bool is_leaf() const { return type == NodeType::TERMINAL; }
};

```

## File: `include/pos_dict.h`

```c
#pragma once
#include <string>

enum class POS {
    DET, N, V, ADJ, ADV, PREP, PRON, CONJ, AUX, NUM, PROPER_N, OP, LPAREN, RPAREN, INTJ, UNKNOWN
};

std::string pos_to_str(POS tag);
POS str_to_pos(const std::string& s);
void load_dictionary(const std::string& filename);
POS lookup_word(const std::string& word);

```

## File: `include/symbol_table.h`

```c
#pragma once
#include "parse_tree.h"
#include <string>
#include <vector>

struct SymbolEntry {
    int index;
    std::string lexeme;
    std::string pos_tag;
    std::string grammar_role;
    std::string scope;
};

class SymbolTable {
public:
    void build(const ParseNode* root);
    void print() const;
    const std::vector<SymbolEntry>& entries() const;

private:
    std::vector<SymbolEntry> entries_;
    int counter_ = 1;
    void traverse(const ParseNode* node, const std::string& parent_label, const std::string& scope);
};

```

## File: `include/top_down_parser.h`

```c
#pragma once
#include "lexer.h"
#include "parse_tree.h"
#include <vector>
#include <memory>

class TopDownParser {
public:
    explicit TopDownParser(const std::vector<Token>& tokens);
    std::unique_ptr<ParseNode> parse();

private:
    std::vector<Token> tokens_;
    size_t cursor_;

    std::unique_ptr<ParseNode> parse_S();
    std::unique_ptr<ParseNode> parse_S_base();
    std::unique_ptr<ParseNode> parse_NP();
    std::unique_ptr<ParseNode> parse_VP();
    std::unique_ptr<ParseNode> parse_PP();
    std::unique_ptr<ParseNode> parse_ADJ_list();

    std::unique_ptr<ParseNode> parse_EXPR();
    std::unique_ptr<ParseNode> parse_TERM();
    std::unique_ptr<ParseNode> parse_FACTOR();

    const Token& current() const;
    const Token& peek(int offset = 0) const;
    bool consume(POS expected, ParseNode* parent);
    bool at_end() const;
};

```

## File: `scripts/run_smoke_tests`

```text
#!/bin/bash
g++ -std=c++17 src/*.cpp -Iinclude -o english-parser

echo "Running Smoke Tests (Top-Down)"
echo "------------------------------"
fail_count=0
while IFS= read -r line || [[ -n "$line" ]]; do
    if ./english-parser "$line" > /dev/null 2>&1; then
        echo "[  OK  ] $line"
    else
        echo "[ FAIL ] $line"
        fail_count=$((fail_count+1))
    fi
done < tests/fixtures/sentences.txt

echo ""
echo "Running Smoke Tests (Bottom-Up)"
echo "-------------------------------"
# Bottom-Up doesn't support math expressions yet based on phase 6 instructions,
# but we can test the english sentences.
head -n 6 tests/fixtures/sentences.txt | while IFS= read -r line || [[ -n "$line" ]]; do
    if ./english-parser --bottom-up "$line" > /dev/null 2>&1; then
        echo "[  OK  ] $line"
    else
        echo "[ FAIL ] $line"
        fail_count=$((fail_count+1))
    fi
done

echo ""
if [ $fail_count -eq 0 ]; then
    echo "All smoke tests passed!"
    exit 0
else
    echo "$fail_count smoke tests failed."
    exit 1
fi

```

## File: `src/bottom_up_parser.cpp`

```cpp
#include "bottom_up_parser.h"
#include <algorithm>
#include <iostream>

BottomUpParser::BottomUpParser(const std::vector<Token>& tokens) 
    : tokens_(tokens), input_pos_(0) {}

bool BottomUpParser::at_end() const {
    return input_pos_ >= tokens_.size();
}

std::unique_ptr<ParseNode> BottomUpParser::parse() {
    input_pos_ = 0;
    stack_.clear();
    
    int loop_counter = 0;
    int max_loops = tokens_.size() * 10;

    while (loop_counter++ < max_loops) {
        if (stack_.size() == 1 && stack_.back().symbol == "S" && at_end()) {
            return std::move(stack_.back().node);
        }

        if (try_reduce()) {
            std::cout << "Reduced: " << stack_.back().symbol << " (Stack size: " << stack_.size() << ")";
            if (stack_.back().node) {
                 std::cout << " Node labels: ";
                 for (const auto& child : stack_.back().node->children) {
                     std::cout << child->label << " ";
                 }
            }
            std::cout << std::endl;
            continue;
        } else if (!at_end()) {
            shift();
            std::cout << "Shifted: " << stack_.back().symbol << " (" << stack_.back().node->lexeme << ")" << std::endl;
        } else {
            // Stuck: Cannot shift and cannot reduce, but not in accept state
            // One last check: can we reduce S S to S or NP S to S?
            return nullptr;
        }
    }
    
    return nullptr; // Infinite loop guard triggered
}

void BottomUpParser::shift() {
    if (at_end()) return;

    auto& token = tokens_[input_pos_++];
    auto node = std::make_unique<ParseNode>();
    
    node->label = pos_to_str(token.tag);
    node->lexeme = token.word;
    node->type = NodeType::TERMINAL;
    
    stack_.push_back({std::move(node), pos_to_str(token.tag)});
}

bool BottomUpParser::stack_top_matches(const std::vector<std::string>& pattern) const {
    if (stack_.size() < pattern.size()) return false;
    
    size_t stack_idx = stack_.size() - pattern.size();
    for (size_t i = 0; i < pattern.size(); ++i) {
        if (stack_[stack_idx + i].symbol != pattern[i]) {
            return false;
        }
    }
    return true;
}

bool BottomUpParser::try_reduce() {
    if (reduce_PP()) return true;
    if (reduce_VP()) return true;
    if (reduce_S()) return true;
    if (reduce_NP()) return true;

    return false;
}

bool BottomUpParser::reduce_PP() {
    if (stack_top_matches({"PREP", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "PP";
        node->type = NodeType::NON_TERMINAL;
        
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto prep = std::move(stack_.back().node); stack_.pop_back();
        
        node->add_child(std::move(prep));
        node->add_child(std::move(np));
        
        stack_.push_back({std::move(node), "PP"});
        return true;
    }
    return false;
}

bool BottomUpParser::reduce_NP() {
    if (stack_top_matches({"NP", "PRON", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP"; node->type = NodeType::NON_TERMINAL;
        auto s_node = std::move(stack_.back().node); stack_.pop_back();
        auto pron = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        node->add_child(std::move(pron));
        node->add_child(std::move(s_node));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"NP", "PRON", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP"; node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto pron = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        node->add_child(std::move(pron));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    
    if (stack_top_matches({"NP", "CONJ", "NP"})) {
        if (stack_[stack_.size()-2].node->lexeme == "and" || stack_[stack_.size()-2].node->lexeme == "or") {
            auto node = std::make_unique<ParseNode>();
            node->label = "NP"; node->type = NodeType::NON_TERMINAL;
            auto np2 = std::move(stack_.back().node); stack_.pop_back();
            auto conj = std::move(stack_.back().node); stack_.pop_back();
            auto np1 = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(np1));
            node->add_child(std::move(conj));
            node->add_child(std::move(np2));
            stack_.push_back({std::move(node), "NP"});
            return true;
        }
    }

    if (stack_top_matches({"NP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"DET", "NUM", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        auto num = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(num));
        node->add_child(std::move(adj));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"DET", "ADJ", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj2 = std::move(stack_.back().node); stack_.pop_back();
        auto adj1 = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(adj1));
        node->add_child(std::move(adj2));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }


    if (stack_top_matches({"DET", "DET", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto det2 = std::move(stack_.back().node); stack_.pop_back();
        auto det1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det1));
        node->add_child(std::move(det2));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"DET", "N", "N", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n3 = std::move(stack_.back().node); stack_.pop_back();
        auto n2 = std::move(stack_.back().node); stack_.pop_back();
        auto n1 = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(n1));
        node->add_child(std::move(n2));
        node->add_child(std::move(n3));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"DET", "V", "N", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n2 = std::move(stack_.back().node); stack_.pop_back();
        auto n1 = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(v));
        node->add_child(std::move(n1));
        node->add_child(std::move(n2));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"DET", "ADJ", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj2 = std::move(stack_.back().node); stack_.pop_back();
        auto adj1 = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(adj1));
        node->add_child(std::move(adj2));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"DET", "DET", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto det2 = std::move(stack_.back().node); stack_.pop_back();
        auto det1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det1));
        node->add_child(std::move(det2));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"DET", "NUM", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto num = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(num));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"DET", "V", "N"})) {
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") {
            // Do not eagerly reduce, allow DET V N N to match
        } else {
            auto node = std::make_unique<ParseNode>();
            node->label = "NP";
            node->type = NodeType::NON_TERMINAL;
            auto n = std::move(stack_.back().node); stack_.pop_back();
            auto v = std::move(stack_.back().node); stack_.pop_back();
            auto det = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(det));
            node->add_child(std::move(v));
            node->add_child(std::move(n));
            stack_.push_back({std::move(node), "NP"});
            return true;
        }
    }

    if (stack_top_matches({"DET", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(adj));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"DET", "N", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n2 = std::move(stack_.back().node); stack_.pop_back();
        auto n1 = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(n1));
        node->add_child(std::move(n2));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"NUM", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        auto num = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(num));
        node->add_child(std::move(adj));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"ADJ", "ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj2 = std::move(stack_.back().node); stack_.pop_back();
        auto adj1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adj1));
        node->add_child(std::move(adj2));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"DET", "N"})) {
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") return false;

        auto node = std::make_unique<ParseNode>();

        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto det = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(det));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"NUM", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto num = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(num));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"V", "N"})) {
        if (stack_.size() >= 3 && (stack_[stack_.size()-3].symbol == "NP" || stack_[stack_.size()-3].symbol == "AUX" || stack_[stack_.size()-3].symbol == "DET")) {
            // Do not reduce V N, let it be V NP
        } else {
            auto node = std::make_unique<ParseNode>();
            node->label = "NP";
            node->type = NodeType::NON_TERMINAL;
            auto n = std::move(stack_.back().node); stack_.pop_back();
            auto v = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(v));
            node->add_child(std::move(n));
            stack_.push_back({std::move(node), "NP"});
            return true;
        }
    }

    if (stack_top_matches({"ADJ", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adj));
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"ADJ", "V"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adj));
        node->add_child(std::move(v));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"N", "N", "N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n3 = std::move(stack_.back().node); stack_.pop_back();
        auto n2 = std::move(stack_.back().node); stack_.pop_back();
        auto n1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(n1));
        node->add_child(std::move(n2));
        node->add_child(std::move(n3));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"N", "N"})) {
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") return false;
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n2 = std::move(stack_.back().node); stack_.pop_back();
        auto n1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(n1));
        node->add_child(std::move(n2));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"V"})) {
        // Look ahead: if next is EOF or ADV, maybe it's S -> VP or VP -> V?
        // If it's DET V, it's definitely an NP (e.g. "the building")
        if (stack_.size() > 1 && stack_[stack_.size()-2].symbol == "DET") {
             auto node = std::make_unique<ParseNode>();
             node->label = "NP";
             node->type = NodeType::NON_TERMINAL;
             auto v = std::move(stack_.back().node); stack_.pop_back();
             node->add_child(std::move(v));
             stack_.push_back({std::move(node), "NP"});
             return true;
        }

        bool should_reduce_to_np = false;
        if (stack_.size() > 1 && stack_[stack_.size() - 2].symbol == "PREP") should_reduce_to_np = true;
        if (stack_.size() > 1 && stack_[stack_.size() - 2].symbol == "V") should_reduce_to_np = true;
        // DO NOT reduce V to NP if it's acting as a predicate in NP VP or if it's the start of a VP
        if (stack_.size() > 1 && (stack_[stack_.size()-2].symbol == "DET" || stack_[stack_.size()-2].symbol == "ADJ")) should_reduce_to_np = true;
        
        if (!at_end() && (pos_to_str(tokens_[input_pos_].tag) == "AUX" || pos_to_str(tokens_[input_pos_].tag) == "V")) should_reduce_to_np = true;
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") should_reduce_to_np = false;
        
        // Fix: If it's "young boy", young is ADJ, boy is N but might be V. 
        // If boy is V, and it's DET ADJ V, we should reduce V to NP only if it's not the main verb.
        // But the shift logic already tried to tag it.
        
        if (should_reduce_to_np) {
            auto node = std::make_unique<ParseNode>();
            node->label = "NP";
            node->type = NodeType::NON_TERMINAL;
            auto v = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(v));
            stack_.push_back({std::move(node), "NP"});
            return true;
        }
    }

    if (stack_top_matches({"NP", "PRON"})) {
         return false;
    }

    if (stack_top_matches({"PRON"})) {
        if (!at_end() && (tokens_[input_pos_].tag == POS::V || tokens_[input_pos_].tag == POS::AUX || tokens_[input_pos_].tag == POS::N || tokens_[input_pos_].tag == POS::DET)) {
            return false;
        }
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto pron = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(pron));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    if (stack_top_matches({"PROPER_N"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto pn = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(pn));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }

    if (stack_top_matches({"N"})) {
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") return false;
        auto node = std::make_unique<ParseNode>();
        node->label = "NP";
        node->type = NodeType::NON_TERMINAL;
        auto n = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(n));
        stack_.push_back({std::move(node), "NP"});
        return true;
    }
    return false;
}


bool BottomUpParser::reduce_VP() {

    if (stack_top_matches({"AUX", "PREP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto prep = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(prep));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "PREP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto prep = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(prep));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"PREP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto prep = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(prep));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"ADJ"})) {
        // Look ahead: if next is N, do NOT reduce ADJ to VP
        if (!at_end() && pos_to_str(tokens_[input_pos_].tag) == "N") return false;
        
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adj));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"NP", "ADV", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        auto wrap_vp = std::make_unique<ParseNode>();
        wrap_vp->label = "VP"; wrap_vp->type = NodeType::NON_TERMINAL;
        wrap_vp->add_child(std::move(adv));
        wrap_vp->add_child(std::move(vp));
        node->add_child(std::move(wrap_vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"ADV", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adv));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"VP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(vp));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"VP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(vp));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "PREP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto prep = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(prep));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"PREP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto prep = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(prep));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"VP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(vp));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"VP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(vp));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }

    if (stack_top_matches({"AUX", "V", "NP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "V", "NP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "V", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "V", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "V", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "ADV", "V"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(adv));
        node->add_child(std::move(v));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "V"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto v = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(v));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "ADJ"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adj = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(adj));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "NP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "NP", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(np1));
        node->add_child(std::move(np2));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np1));
        node->add_child(std::move(np2));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "NP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "NP"})) {
        // Shift if next is PRON or CONJ?
        if (!at_end()) {
             auto next_tag = pos_to_str(tokens_[input_pos_].tag);
             if (next_tag == "PRON" || next_tag == "CONJ") return false;
             // If next is V, and it's a MAIN verb, we should reduce this VP now
             if (next_tag == "V") {
                int pron_count = 0;
                for (const auto& item : stack_) if (item.symbol == "PRON") pron_count++;
                int remaining_verbs = 0;
                for (size_t i = input_pos_; i < tokens_.size(); ++i) {
                    if (tokens_[i].tag == POS::V || tokens_[i].tag == POS::AUX) remaining_verbs++;
                }
                if (remaining_verbs >= pron_count && pron_count > 0) {
                    // Reduce now so NP PRON S can form
                } else {
                    return false; // Shift next V? Maybe "give students grades"? 
                }
             }
        }
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(np));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"V", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    if (stack_top_matches({"VP"})) {
        // If we have NP PRON VP, we MUST reduce VP to S
        if (stack_.size() >= 3 && stack_[stack_.size()-3].symbol == "NP" && stack_[stack_.size()-2].symbol == "PRON") {
             auto node = std::make_unique<ParseNode>();
             node->label = "S";
             node->type = NodeType::NON_TERMINAL;
             auto vp = std::move(stack_.back().node); stack_.pop_back();
             node->add_child(std::move(vp));
             stack_.push_back({std::move(node), "S"});
             return true;
        }
        return false;
    }

    if (stack_top_matches({"V"})) {
        // Shift if it's the start of the sentence and more tokens follow.
        // BUT wait, TD is doing S -> S S -> VP VP for "Dogs chase cats".
        // In BU, if we shift "Dogs", then shift "chase", then "cats", we get V V N.
        // If we reduce Cats to NP, we have V V NP.
        // If we reduce V NP to VP, we have V VP.
        // If we reduce V to VP, we have VP VP.
        // If we reduce VP to S, we have S VP.
        // If we reduce VP to S, we have S S.
        // Then S S to S.
        
        if (!at_end()) {
            auto next_tag = pos_to_str(tokens_[input_pos_].tag);
            // If next is a verb or NP components, keep shifting to allow longer structures
            if (next_tag == "V" || next_tag == "NP" || next_tag == "N" || next_tag == "DET" || next_tag == "ADJ" || next_tag == "PRON") {
                return false;
            }
        }
        // If it's a verb but sitting at the start of the stack, and there's a verb following, 
        // it might be better as an NP (gerund) OR we should wait and see if it's S -> VP S or S -> VP.
        // But the TD parser is choosing S -> S S -> VP VP.
        
        auto node = std::make_unique<ParseNode>();
        node->label = "VP";
        node->type = NodeType::NON_TERMINAL;
        auto v = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(v));
        stack_.push_back({std::move(node), "VP"});
        return true;
    }
    return false;
}

bool BottomUpParser::reduce_S() {
    if (stack_top_matches({"NP", "VP"})) {
         if (!at_end()) {
             auto next_tag = pos_to_str(tokens_[input_pos_].tag);
             if (next_tag == "PRON" || next_tag == "CONJ") return false;
             
             // If preceded by PRON, reduce immediately to close the relative clause!
             bool inside_rel_clause = (stack_.size() >= 3 && stack_[stack_.size()-3].symbol == "PRON");
             if (!inside_rel_clause) {
                 // Standard shift/reduce delay for main verbs
                 if (next_tag == "V" || next_tag == "AUX" || next_tag == "ADV" || next_tag == "PREP") return false;
             }
         }
         auto node = std::make_unique<ParseNode>();
         node->label = "S";
         node->type = NodeType::NON_TERMINAL;
         auto vp = std::move(stack_.back().node); stack_.pop_back();
         auto np = std::move(stack_.back().node); stack_.pop_back();
         node->add_child(std::move(np));
         node->add_child(std::move(vp));
         stack_.push_back({std::move(node), "S"});
         return true;
    }

    if (stack_top_matches({"NP", "VP", "AUX", "NP"})) {
        // Look ahead: if next is EOF, it's a tag question.
        if (at_end()) {
            auto node = std::make_unique<ParseNode>();
            node->label = "S";
            node->type = NodeType::NON_TERMINAL;
            auto np2 = std::move(stack_.back().node); stack_.pop_back();
            auto aux = std::move(stack_.back().node); stack_.pop_back();
            auto vp = std::move(stack_.back().node); stack_.pop_back();
            auto np1 = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(np1));
            node->add_child(std::move(vp));
            node->add_child(std::move(aux));
            node->add_child(std::move(np2));
            stack_.push_back({std::move(node), "S"});
            return true;
        }
    }

    if (stack_top_matches({"S", "CONJ", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S"; node->type = NodeType::NON_TERMINAL;
        auto s2 = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        auto s1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s1));
        node->add_child(std::move(conj));
        node->add_child(std::move(s2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"CONJ", "S", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s2 = std::move(stack_.back().node); stack_.pop_back();
        auto s1 = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(conj));
        node->add_child(std::move(s1));
        node->add_child(std::move(s2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"ADV", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adv));
        node->add_child(std::move(s));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"AUX", "NP", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np1));
        node->add_child(std::move(np2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"S", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s2 = std::move(stack_.back().node); stack_.pop_back();
        auto s1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s1));
        node->add_child(std::move(s2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"S", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto s = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"S", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto s = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"CONJ", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(conj));
        node->add_child(std::move(s));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"NP", "VP", "CONJ", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np1));
        node->add_child(std::move(vp));
        node->add_child(std::move(conj));
        node->add_child(std::move(np2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"NP", "AUX", "NP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np1));
        node->add_child(std::move(aux));
        node->add_child(std::move(np2));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"NP", "VP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        node->add_child(std::move(vp));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"AUX", "NP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"NP", "ADV", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        auto wrap_vp = std::make_unique<ParseNode>();
        wrap_vp->label = "VP"; wrap_vp->type = NodeType::NON_TERMINAL;
        wrap_vp->add_child(std::move(adv));
        wrap_vp->add_child(std::move(vp));
        node->add_child(std::move(wrap_vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"NP"})) {
        if (at_end()) {
            auto node = std::make_unique<ParseNode>();
            node->label = "S";
            node->type = NodeType::NON_TERMINAL;
            auto np = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(np));
            stack_.push_back({std::move(node), "S"});
            return true;
        }
    }

    if (stack_top_matches({"VP"})) {
        if (at_end()) {
            auto node = std::make_unique<ParseNode>();
            node->label = "S";
            node->type = NodeType::NON_TERMINAL;
            auto vp = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(vp));
            stack_.push_back({std::move(node), "S"});
            return true;
        }
    }

    if (stack_top_matches({"NP", "S"})) {
        if (at_end()) {
            auto node = std::make_unique<ParseNode>();
            node->label = "S";
            node->type = NodeType::NON_TERMINAL;
            auto s = std::move(stack_.back().node); stack_.pop_back();
            auto np = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(np));
            node->add_child(std::move(s));
            stack_.push_back({std::move(node), "S"});
            return true;
        }
    }

    if (stack_top_matches({"INTJ", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s = std::move(stack_.back().node); stack_.pop_back();
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        node->add_child(std::move(s));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"INTJ", "NP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        node->add_child(std::move(np));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"INTJ", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        node->add_child(std::move(np));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"INTJ"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    return false;
}

```

## File: `src/bottom_up_parser.cpp_new`

```cpp_new
bool BottomUpParser::reduce_S() {
    if (stack_top_matches({"NP", "VP", "AUX", "NP"})) {
        // Look ahead: if next is EOF, it's a tag question.
        if (at_end()) {
            auto node = std::make_unique<ParseNode>();
            node->label = "S";
            node->type = NodeType::NON_TERMINAL;
            auto np2 = std::move(stack_.back().node); stack_.pop_back();
            auto aux = std::move(stack_.back().node); stack_.pop_back();
            auto vp = std::move(stack_.back().node); stack_.pop_back();
            auto np1 = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(np1));
            node->add_child(std::move(vp));
            node->add_child(std::move(aux));
            node->add_child(std::move(np2));
            stack_.push_back({std::move(node), "S"});
            return true;
        }
    }

    if (stack_top_matches({"S", "CONJ", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S"; node->type = NodeType::NON_TERMINAL;
        auto s2 = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        auto s1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s1));
        node->add_child(std::move(conj));
        node->add_child(std::move(s2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    // CONJ S S (Longest match first)
    if (stack_top_matches({"CONJ", "S", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s2 = std::move(stack_.back().node); stack_.pop_back();
        auto s1 = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(conj));
        node->add_child(std::move(s1));
        node->add_child(std::move(s2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"ADV", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(adv));
        node->add_child(std::move(s));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np1));
        node->add_child(std::move(np2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"S", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s2 = std::move(stack_.back().node); stack_.pop_back();
        auto s1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s1));
        node->add_child(std::move(s2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"S", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto s = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"S", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto s = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(s));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"NP", "VP", "AUX", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np1));
        node->add_child(std::move(vp));
        node->add_child(std::move(aux));
        node->add_child(std::move(np2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"CONJ", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(conj));
        node->add_child(std::move(s));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"NP", "VP", "CONJ", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto conj = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np1));
        node->add_child(std::move(vp));
        node->add_child(std::move(conj));
        node->add_child(std::move(np2));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"NP", "AUX", "NP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np2 = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        auto np1 = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np1));
        node->add_child(std::move(aux));
        node->add_child(std::move(np2));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"NP", "VP", "PP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto pp = std::move(stack_.back().node); stack_.pop_back();
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        node->add_child(std::move(vp));
        node->add_child(std::move(pp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"AUX", "NP", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto aux = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(aux));
        node->add_child(std::move(np));
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"NP", "ADV", "VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(np));
        auto wrap_vp = std::make_unique<ParseNode>();
        wrap_vp->label = "VP"; wrap_vp->type = NodeType::NON_TERMINAL;
        wrap_vp->add_child(std::move(adv));
        wrap_vp->add_child(std::move(vp));
        node->add_child(std::move(wrap_vp));
        stack_.push_back({std::move(node), "S"});
        return true;
    }

    if (stack_top_matches({"NP", "VP"})) {
         auto node = std::make_unique<ParseNode>();
         node->label = "S";
         node->type = NodeType::NON_TERMINAL;
         auto vp = std::move(stack_.back().node); stack_.pop_back();
         auto np = std::move(stack_.back().node); stack_.pop_back();
         node->add_child(std::move(np));
         node->add_child(std::move(vp));
         stack_.push_back({std::move(node), "S"});
         return true;
    }

    if (stack_top_matches({"NP", "S"})) {
        if (at_end()) {
            auto node = std::make_unique<ParseNode>();
            node->label = "S";
            node->type = NodeType::NON_TERMINAL;
            auto s = std::move(stack_.back().node); stack_.pop_back();
            auto np = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(np));
            node->add_child(std::move(s));
            stack_.push_back({std::move(node), "S"});
            return true;
        }
    }

    if (stack_top_matches({"NP"})) {
        if (at_end()) {
            auto node = std::make_unique<ParseNode>();
            node->label = "S";
            node->type = NodeType::NON_TERMINAL;
            auto np = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(np));
            stack_.push_back({std::move(node), "S"});
            return true;
        }
    }

    if (stack_top_matches({"VP"})) {
        if (at_end()) {
            auto node = std::make_unique<ParseNode>();
            node->label = "S";
            node->type = NodeType::NON_TERMINAL;
            auto vp = std::move(stack_.back().node); stack_.pop_back();
            node->add_child(std::move(vp));
            stack_.push_back({std::move(node), "S"});
            return true;
        }
    }

    if (stack_top_matches({"INTJ", "S"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto s = std::move(stack_.back().node); stack_.pop_back();
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        node->add_child(std::move(s));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"INTJ", "NP", "ADV"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto adv = std::move(stack_.back().node); stack_.pop_back();
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        node->add_child(std::move(np));
        node->add_child(std::move(adv));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"INTJ", "NP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto np = std::move(stack_.back().node); stack_.pop_back();
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        node->add_child(std::move(np));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    if (stack_top_matches({"INTJ"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto intj = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(intj));
        stack_.push_back({std::move(node), "S"});
        return true;
    }
    return false;
}

```

## File: `src/display.cpp`

```cpp
#include "display.h"
#include <iostream>
#include <algorithm>
#include <fstream>

namespace {
    int utf8_length(const std::string& str) {
        int len = 0;
        for (size_t i = 0; i < str.length(); ++i) {
            if ((str[i] & 0xC0) != 0x80) len++;
        }
        return len;
    }
}

void Display::print_tree(const ParseNode* root) {
    if (!root) return;
    auto lines = render_tree_2d(root);
    for (const auto& line : lines) {
        std::cout << line << "\n";
    }
    std::cout << "\n";
}

void Display::export_dot(const ParseNode* root, const std::string& filename) {
    if (!root) return;
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing.\n";
        return;
    }
    
    out << "digraph ParseTree {\n";
    out << "    node [shape=box, style=rounded, fontname=\"Helvetica,Arial,sans-serif\"];\n";
    out << "    edge [dir=none];\n";
    
    int id_counter = 0;
    export_dot_node(root, id_counter, out);
    
    out << "}\n";
    out.close();
    std::cout << "Parse tree exported to " << filename << ".\n";
    std::cout << "You can render it using Graphviz: dot -Tpng " << filename << " -o tree.png\n";
}

void Display::export_dot_node(const ParseNode* node, int& id_counter, std::ofstream& out) {
    int current_id = id_counter++;
    
    if (node->is_leaf()) {
        out << "    node" << current_id << " [label=\"" << node->label << "\\n\\\"" << node->lexeme << "\\\"\", shape=ellipse];\n";
    } else {
        out << "    node" << current_id << " [label=\"" << node->label << "\"];\n";
    }
    
    for (const auto& child : node->children) {
        int child_id = id_counter;
        out << "    node" << current_id << " -> node" << child_id << ";\n";
        export_dot_node(child.get(), id_counter, out);
    }
}

std::vector<std::string> Display::render_tree_2d(const ParseNode* node) {
    std::vector<std::string> res;
    
    if (node->is_leaf()) {
        std::string l1 = node->label;
        std::string l2 = "\"" + node->lexeme + "\"";
        int w = std::max(l1.length(), l2.length());
        std::string line1(w, ' ');
        std::string line2(w, ' ');
        
        int start1 = (w - l1.length()) / 2;
        int start2 = (w - l2.length()) / 2;
        
        for (int i=0; i<l1.length(); i++) line1[start1+i] = l1[i];
        for (int i=0; i<l2.length(); i++) line2[start2+i] = l2[i];
        
        res.push_back(line1);
        res.push_back(line2);
        return res;
    }
    
    if (node->children.empty()) {
        return {node->label};
    }

    std::vector<std::vector<std::string>> child_blocks;
    for (const auto& child : node->children) {
        child_blocks.push_back(render_tree_2d(child.get()));
    }

    int max_h = 0;
    for (const auto& block : child_blocks) {
        if (block.size() > max_h) max_h = block.size();
    }

    int gap = 2; // minimum gap between subtrees
    std::vector<std::string> combined(max_h, "");
    std::vector<int> centers;

    for (size_t i = 0; i < child_blocks.size(); ++i) {
        int child_w = 0;
        if (!child_blocks[i].empty()) {
            child_w = utf8_length(child_blocks[i][0]);
        }
        
        int center_offset = child_w / 2;
        int current_width = utf8_length(combined[0]);
        centers.push_back(current_width + center_offset);

        for (int h = 0; h < max_h; ++h) {
            std::string block_line;
            if (h < child_blocks[i].size()) {
                block_line = child_blocks[i][h];
            } else {
                block_line = std::string(child_w, ' ');
            }
            combined[h] += block_line;
            if (i < child_blocks.size() - 1) {
                combined[h] += std::string(gap, ' ');
            }
        }
    }

    int total_w = utf8_length(combined[0]);
    int p_center = centers.size() == 1 ? centers[0] : (centers.front() + centers.back()) / 2;
    int p_w = utf8_length(node->label);

    int diff = p_w - total_w;
    if (diff > 0) {
        int pad_l = diff / 2;
        int pad_r = diff - pad_l;
        for (auto& s : combined) {
            s = std::string(pad_l, ' ') + s + std::string(pad_r, ' ');
        }
        for (auto& c : centers) c += pad_l;
        p_center += pad_l;
        total_w = p_w;
    }

    int p_start = p_center - p_w / 2;
    if (p_start < 0) {
        int shift = -p_start;
        for (auto& s : combined) s = std::string(shift, ' ') + s;
        for (auto& c : centers) c += shift;
        p_center += shift;
        p_start = 0;
        total_w += shift;
    }
    
    if (p_start + p_w > total_w) {
        int shift = p_start + p_w - total_w;
        for (auto& s : combined) s += std::string(shift, ' ');
        total_w += shift;
    }

    std::string p_line(total_w, ' ');
    for (int i = 0; i < p_w; ++i) {
        p_line[p_start + i] = node->label[i];
    }

    std::string b_line = "";
    for(int i=0; i<total_w; ++i) {
        if (centers.size() == 1) {
            if (i == centers[0]) b_line += "│";
            else b_line += " ";
        } else {
            bool is_center = (i == p_center);
            bool is_child = std::find(centers.begin(), centers.end(), i) != centers.end();
            bool is_between = i > centers.front() && i < centers.back();

            if (is_center && is_child) b_line += "┼";
            else if (is_center) b_line += "┴";
            else if (is_child && i == centers.front()) b_line += "┌";
            else if (is_child && i == centers.back()) b_line += "┐";
            else if (is_child) b_line += "┬";
            else if (is_between) b_line += "─";
            else b_line += " ";
        }
    }

    res.push_back(p_line);
    res.push_back(b_line);
    for (const auto& s : combined) res.push_back(s);

    return res;
}

void Display::print_strategy(const std::string& name) {
    std::cout << "========================================\n";
    std::cout << " Parsing Strategy: " << name << "\n";
    std::cout << "========================================\n\n";
}

void Display::print_symbol_table(const SymbolTable& table) {
    table.print();
}

```

## File: `src/lexer.cpp`

```cpp
#include "lexer.h"
#include <cctype>
#include <sstream>
#include <algorithm>

Lexer::Lexer(const std::string& input) : input_(input) {}

std::vector<std::string> Lexer::split_words(const std::string& s) {
    std::vector<std::string> words;
    std::string current_word = "";
    
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        
        if (std::isspace(c)) {
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
            words.push_back(std::string(1, c));
        } else if (c == '.' || c == ',' || c == ':' || c == ';' || c == '!' || c == '?') {
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
        } else if (c == '\'') {
            continue; // Strips apostrophe so "won't" becomes "wont"
        } else if (std::isdigit(c)) {
            if (!current_word.empty() && !std::isdigit(current_word[0])) {
                words.push_back(current_word);
                current_word.clear();
            }
            current_word += c;
        } else {
            current_word += c;
        }
    }
    if (!current_word.empty()) {
        words.push_back(current_word);
    }
    return words;
}

POS Lexer::assign_pos(const std::string& word, bool is_first_word) {
    if (word.empty()) return POS::UNKNOWN;
    
    if (word == "+" || word == "-" || word == "*" || word == "/") return POS::OP;
    if (word == "(") return POS::LPAREN;
    if (word == ")") return POS::RPAREN;
    
    bool is_all_digits = true;
    for (char c : word) {
        if (!std::isdigit(c)) {
            is_all_digits = false;
            break;
        }
    }
    if (is_all_digits) return POS::NUM;

    std::string lower_word = word;
    std::transform(lower_word.begin(), lower_word.end(), lower_word.begin(),
                   [](unsigned char c){ return std::tolower(c); });
                   
    if (lower_word == "that") return POS::PRON;

    POS tag = lookup_word(lower_word);
    if (tag != POS::UNKNOWN) {
        return tag;
    }

    if (lower_word.size() > 3 && lower_word.substr(lower_word.size() - 3) == "ing") {
        return POS::V;
    }
    if (lower_word.size() >= 4 && lower_word.substr(lower_word.size() - 2) == "ly") {
        return POS::ADV;
    }
    if (lower_word.size() > 2 && lower_word.substr(lower_word.size() - 2) == "ed") {
        return POS::V;
    }
    if ((lower_word.size() > 4 && lower_word.substr(lower_word.size() - 4) == "tion") ||
        (lower_word.size() > 4 && lower_word.substr(lower_word.size() - 4) == "ness") ||
        (lower_word.size() > 4 && lower_word.substr(lower_word.size() - 4) == "ment")) {
        return POS::N;
    }

    if (!is_first_word && std::isupper(word[0])) {
        return POS::PROPER_N;
    }

    return POS::N;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    std::vector<std::string> words = split_words(input_);
    
    for (size_t i = 0; i < words.size(); ++i) {
        bool is_first = (i == 0);
        POS tag = assign_pos(words[i], is_first);
        tokens.push_back({words[i], tag, static_cast<int>(i)});
    }
    
    return tokens;
}

```

## File: `src/main.cpp`

```cpp
#include "lexer.h"
#include "top_down_parser.h"
#include "bottom_up_parser.h"
#include "display.h"
#include "pos_dict.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    load_dictionary("data/dictionary.txt");

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [--bottom-up] [--dot filename] \"sentence to parse\"" << std::endl;
        return 1;
    }

    bool use_bottom_up = false;
    std::string dot_filename = "";
    std::string input = "";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--bottom-up") {
            use_bottom_up = true;
        } else if (arg == "--top-down") {
            // Skip
        } else if (arg == "--dot" && i + 1 < argc) {
            dot_filename = argv[++i];
        } else {
            input = arg;
        }
    }

    if (input.empty()) {
        std::cerr << "Error: No input sentence provided." << std::endl;
        return 1;
    }

    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();
    std::unique_ptr<ParseNode> root;

    if (use_bottom_up) {
        BottomUpParser parser(tokens);
        root = parser.parse();
        Display::print_strategy("Bottom-Up (Shift-Reduce)");
    } else {
        TopDownParser parser(tokens);
        root = parser.parse();
        Display::print_strategy("Top-Down (Recursive Descent)");
    }

    if (root) {
        Display::print_tree(root.get());
        
        if (!dot_filename.empty()) {
            Display::export_dot(root.get(), dot_filename);
        }
        
        bool is_expr = false;
        for (const auto& token : tokens) {
            if (token.tag == POS::OP) {
                is_expr = true;
                break;
            }
        }
        if (!is_expr && tokens.size() > 0) {
            is_expr = true;
            for (const auto& token : tokens) {
                if (token.tag != POS::NUM && token.tag != POS::OP && token.tag != POS::LPAREN && token.tag != POS::RPAREN) {
                    is_expr = false;
                    break;
                }
            }
        }
        
        if (!is_expr) {
            std::cout << "\nSymbol Table:\n";
            SymbolTable table;
            table.build(root.get());
            Display::print_symbol_table(table);
        }
    } else {
        std::cerr << "Error: Could not parse input as a valid sentence or expression." << std::endl;
        return 1;
    }

    return 0;
}

```

## File: `src/parse_tree.cpp`

```cpp
#include "parse_tree.h"

void ParseNode::add_child(std::unique_ptr<ParseNode> child) {
    if (child) {
        children.push_back(std::move(child));
    }
}

```

## File: `src/pos_dict.cpp`

```cpp
#include "pos_dict.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// Runtime dictionary — populated by load_dictionary()
static std::unordered_map<std::string, POS> DICTIONARY;

std::string pos_to_str(POS tag) {
    switch(tag) {
        case POS::DET:     return "DET";
        case POS::N:       return "N";
        case POS::V:       return "V";
        case POS::ADJ:     return "ADJ";
        case POS::ADV:     return "ADV";
        case POS::PREP:    return "PREP";
        case POS::PRON:    return "PRON";
        case POS::CONJ:    return "CONJ";
        case POS::AUX:     return "AUX";
        case POS::NUM:     return "NUM";
        case POS::PROPER_N:return "PROPER_N";
        case POS::OP:      return "OP";
        case POS::LPAREN:  return "LPAREN";
        case POS::RPAREN:  return "RPAREN";
        case POS::INTJ:    return "INTJ";
        case POS::UNKNOWN: return "UNKNOWN";
        default:           return "UNKNOWN";
    }
}

POS str_to_pos(const std::string& s) {
    if (s == "DET")      return POS::DET;
    if (s == "N")        return POS::N;
    if (s == "V")        return POS::V;
    if (s == "ADJ")      return POS::ADJ;
    if (s == "ADV")      return POS::ADV;
    if (s == "PREP")     return POS::PREP;
    if (s == "PRON")     return POS::PRON;
    if (s == "CONJ")     return POS::CONJ;
    if (s == "AUX")      return POS::AUX;
    if (s == "NUM")      return POS::NUM;
    if (s == "PROPER_N") return POS::PROPER_N;
    if (s == "INTJ")     return POS::INTJ;
    return POS::UNKNOWN;
}

void load_dictionary(const std::string& filename) {
    // Seed with minimal fallback so parser works even without the file
    DICTIONARY = {
        {"the",POS::DET},{"a",POS::DET},{"an",POS::DET},
        {"is",POS::AUX},{"are",POS::AUX},{"was",POS::AUX},
        {"he",POS::PRON},{"she",POS::PRON},{"it",POS::PRON},
        {"they",POS::PRON},{"i",POS::PRON},{"you",POS::PRON},
        {"we",POS::PRON},{"him",POS::PRON},{"her",POS::DET},
        {"and",POS::CONJ},{"but",POS::CONJ},{"or",POS::CONJ},
        {"in",POS::PREP},{"on",POS::PREP},{"at",POS::PREP},
        {"to",POS::PREP},{"over",POS::PREP},{"with",POS::PREP},
    };

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: dictionary file '" << filename
                  << "' not found. Parser will use suffix heuristics only.\n";
        return;
    }

    std::string line;
    int loaded = 0;
    while (std::getline(file, line)) {
        // Strip comments (# to end of line)
        auto hash = line.find('#');
        if (hash != std::string::npos) line = line.substr(0, hash);

        std::istringstream iss(line);
        std::string word, tag_str;
        if (!(iss >> word >> tag_str)) continue;

        POS tag = str_to_pos(tag_str);
        if (tag == POS::UNKNOWN) continue;

        // Lowercase all keys — lookup is always case-insensitive
        std::transform(word.begin(), word.end(), word.begin(),
            [](unsigned char c){ return std::tolower(c); });
        DICTIONARY[word] = tag;
        loaded++;
    }
    std::cerr << "Loaded " << loaded << " dictionary entries from " << filename << "\n";
}

POS lookup_word(const std::string& word) {
    auto it = DICTIONARY.find(word);
    return (it != DICTIONARY.end()) ? it->second : POS::UNKNOWN;
}
```

## File: `src/symbol_table.cpp`

```cpp
#include "symbol_table.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void SymbolTable::build(const ParseNode* root) {
    entries_.clear();
    counter_ = 1;
    if (root) {
        traverse(root, "", "Sentence");
    }
}

void SymbolTable::traverse(const ParseNode* node, const std::string& parent_label, const std::string& scope) {
    if (!node) return;

    if (node->is_leaf()) {
        std::string role;
        
        if (parent_label == "NP" || parent_label == "NP_participle") {
            if (node->label == "DET") role = "NP.determiner";
            else if (node->label == "NUM") role = "NP.quantity";
            else if (node->label == "PRON" && (node->lexeme == "who" || node->lexeme == "that" || node->lexeme == "which")) role = "NP.relative_pronoun";
            else if (node->label == "N" || node->label == "PRON" || node->label == "PROPER_N") role = "NP.head";
            else if (node->label == "V") {
                if (parent_label == "NP_participle") role = "NP.participle_modifier";
                else role = "NP.gerund";
            }
            else if (node->label == "ADJ") role = "NP.modifier";
            else role = "NP." + node->label;
        } else if (parent_label == "VP") {
            if (node->label == "V") role = "VP.head";
            else if (node->label == "AUX") role = "VP.auxiliary";
            else if (node->label == "ADV") role = "VP.modifier";
            else if (node->label == "ADV" || node->label == "ADJ") role = "VP.modifier";
            else if (node->label == "PREP") role = "VP.infinitive_marker";
            else role = parent_label + "." + node->label;
        } else if (parent_label == "PP") {
            if (node->label == "PREP") role = "PP.head";
            else role = parent_label + "." + node->label;
        } else if (parent_label == "S" && node->label == "INTJ") {
            role = "S.interjection";
        } else if (parent_label == "S" && node->label == "AUX") {
            role = "S.auxiliary";
        } else if (parent_label == "S" && node->label == "CONJ") {
            role = "S.conjunction";
        } else if (parent_label == "S" && node->label == "ADV") {
            role = "S.modifier";
        } else if (parent_label == "VP" && node->label == "PREP") {
            role = "VP.infinitive_marker";
        } else {
            role = parent_label + "." + node->label;
        }

        entries_.push_back({counter_++, node->lexeme, node->label, role, scope});
    } else {
        std::string next_scope = scope;
        if (node->label == "PP") {
            next_scope = "Prepositional";
        }
        
        for (size_t i = 0; i < node->children.size(); ++i) {
            auto& child = node->children[i];
            std::string pass_label = node->label;
            if (node->label == "NP" && child->label == "V") {
                if (i + 1 < node->children.size() && node->children[i+1]->label == "N") {
                    pass_label = "NP_participle";
                }
            }
            traverse(child.get(), pass_label, next_scope);
        }
    }
}

const std::vector<SymbolEntry>& SymbolTable::entries() const {
    return entries_;
}

void SymbolTable::print() const {
    if (entries_.empty()) return;

    // Calculate column widths
    size_t w_idx = 5; // "Index"
    size_t w_lex = 6; // "Lexeme"
    size_t w_pos = 7; // "POS Tag"
    size_t w_rol = 12; // "Grammar Role"
    size_t w_sco = 5; // "Scope"

    for (const auto& e : entries_) {
        w_lex = std::max(w_lex, e.lexeme.length());
        w_pos = std::max(w_pos, e.pos_tag.length());
        w_rol = std::max(w_rol, e.grammar_role.length());
        w_sco = std::max(w_sco, e.scope.length());
    }

    std::string line = "├" + std::string(w_idx + 2, '-') + "┼" 
                     + std::string(w_lex + 2, '-') + "┼" 
                     + std::string(w_pos + 2, '-') + "┼" 
                     + std::string(w_rol + 2, '-') + "┼" 
                     + std::string(w_sco + 2, '-') + "┤\n";
                     
    std::string top_line = "┌" + std::string(w_idx + 2, '-') + "┬" 
                         + std::string(w_lex + 2, '-') + "┬" 
                         + std::string(w_pos + 2, '-') + "┬" 
                         + std::string(w_rol + 2, '-') + "┬" 
                         + std::string(w_sco + 2, '-') + "┐\n";

    std::string bot_line = "└" + std::string(w_idx + 2, '-') + "┴" 
                         + std::string(w_lex + 2, '-') + "┴" 
                         + std::string(w_pos + 2, '-') + "┴" 
                         + std::string(w_rol + 2, '-') + "┴" 
                         + std::string(w_sco + 2, '-') + "┘\n";

    std::cout << top_line;
    std::cout << "│ " << std::left << std::setw(w_idx) << "Index" << " │ "
              << std::setw(w_lex) << "Lexeme" << " │ "
              << std::setw(w_pos) << "POS Tag" << " │ "
              << std::setw(w_rol) << "Grammar Role" << " │ "
              << std::setw(w_sco) << "Scope" << " │\n";
    std::cout << line;

    for (const auto& e : entries_) {
        std::cout << "│ " << std::left << std::setw(w_idx) << e.index << " │ "
                  << std::setw(w_lex) << e.lexeme << " │ "
                  << std::setw(w_pos) << e.pos_tag << " │ "
                  << std::setw(w_rol) << e.grammar_role << " │ "
                  << std::setw(w_sco) << e.scope << " │\n";
    }
    std::cout << bot_line;
}

```

## File: `src/top_down_parser.cpp`

```cpp
#include "top_down_parser.h"
#include <iostream>

TopDownParser::TopDownParser(const std::vector<Token>& tokens) 
    : tokens_(tokens), cursor_(0) {}

std::unique_ptr<ParseNode> TopDownParser::parse() {
    cursor_ = 0;

    bool is_expr = false;
    for (const auto& token : tokens_) {
        if (token.tag == POS::OP) {
            is_expr = true;
            break;
        }
    }
    // Only treat as expression if ALL tokens are math-related (NUM, OP, PAREN)
    // AND there's at least one NUM or OP.
    if (!is_expr && tokens_.size() > 0) {
        bool all_math = true;
        bool has_val = false;
        for (const auto& token : tokens_) {
            if (token.tag != POS::NUM && token.tag != POS::OP && token.tag != POS::LPAREN && token.tag != POS::RPAREN) {
                all_math = false;
                break;
            }
            if (token.tag == POS::NUM) has_val = true;
        }
        if (all_math && has_val) is_expr = true;
    }

    std::unique_ptr<ParseNode> root;
    if (is_expr) {
        root = parse_EXPR();
    } else {
        root = parse_S();
    }
    
    if (root && at_end()) {
        return root;
    }
    
    return nullptr;
}

const Token& TopDownParser::current() const {
    if (at_end()) {
        static const Token EOF_TOKEN{"", POS::UNKNOWN, -1};
        return EOF_TOKEN;
    }
    return tokens_[cursor_];
}

const Token& TopDownParser::peek(int offset) const {
    if (cursor_ + offset >= tokens_.size()) {
        static const Token EOF_TOKEN{"", POS::UNKNOWN, -1};
        return EOF_TOKEN;
    }
    return tokens_[cursor_ + offset];
}

bool TopDownParser::at_end() const {
    return cursor_ >= tokens_.size();
}

bool TopDownParser::consume(POS expected, ParseNode* parent) {
    if (at_end()) return false;
    
    POS actual = current().tag;
    bool match = (actual == expected);
    
    // Fallback for V/N ambiguity
    // DISABLE fallback for N as V to prevent V from being stolen by NP
    if (!match) {
        if (expected == POS::V && actual == POS::N) match = true;
    }

    if (getenv("PARSER_DEBUG")) {
        std::cout << "Consuming " << pos_to_str(expected) << "? Actual: " << pos_to_str(actual) << " (" << current().word << ") -> " << (match ? "MATCH" : "FAIL") << std::endl;
    }

    if (match) {
        auto leaf = std::make_unique<ParseNode>();
        leaf->label = pos_to_str(expected);
        leaf->lexeme = current().word;
        leaf->type = NodeType::TERMINAL;
        parent->add_child(std::move(leaf));
        cursor_++;
        return true;
    }
    return false;
}

std::unique_ptr<ParseNode> TopDownParser::parse_S() {
    if (getenv("PARSER_DEBUG")) std::cout << "Entering parse_S at " << current().word << std::endl;
    size_t saved_cursor = cursor_;
    std::unique_ptr<ParseNode> s_node = nullptr;

    // S -> NP VP
    {
        auto s2 = std::make_unique<ParseNode>();
        s2->label = "S";
        s2->type = NodeType::NON_TERMINAL;
        if (auto np = parse_NP()) {
            if (auto vp = parse_VP()) {
                s2->add_child(std::move(np));
                s2->add_child(std::move(vp));
                s_node = std::move(s2);
            }
        }
        if (s_node) {
            // Check if we consumed all tokens. If not, maybe it's S -> S S or something else.
            if (at_end()) goto post_process;
            else {
                cursor_ = saved_cursor;
                s_node = nullptr;
            }
        }
        cursor_ = saved_cursor;
    }

    // S -> ADV S (Handles Wh- questions like "Why do we...")
    {
        auto s_adv_s = std::make_unique<ParseNode>();
        s_adv_s->label = "S";
        s_adv_s->type = NodeType::NON_TERMINAL;
        if (consume(POS::ADV, s_adv_s.get())) {
            if (auto s_child = parse_S()) {
                s_adv_s->add_child(std::move(s_child));
                s_node = std::move(s_adv_s);
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_conj_s_s = std::make_unique<ParseNode>();
        s_conj_s_s->label = "S";
        s_conj_s_s->type = NodeType::NON_TERMINAL;
        if (consume(POS::CONJ, s_conj_s_s.get())) {
            // S -> CONJ S S (Longest match: Although S S)
            if (auto s1_child = parse_S()) {
                s_conj_s_s->add_child(std::move(s1_child));
                if (auto s2_child = parse_S()) {
                    s_conj_s_s->add_child(std::move(s2_child));
                    s_node = std::move(s_conj_s_s);
                }
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    // S -> S CONJ S (I went home because it rained)
    {
        auto s_s_conj_s = std::make_unique<ParseNode>();
        s_s_conj_s->label = "S"; s_s_conj_s->type = NodeType::NON_TERMINAL;
        if (auto s1 = parse_S_base()) {
            if (consume(POS::CONJ, s_s_conj_s.get())) {
                if (auto s2 = parse_S()) {
                     s_s_conj_s->add_child(std::move(s1));
                     s_s_conj_s->add_child(std::move(s2));
                     s_node = std::move(s_s_conj_s);
                }
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_conj_s = std::make_unique<ParseNode>();
        s_conj_s->label = "S";
        s_conj_s->type = NodeType::NON_TERMINAL;
        if (consume(POS::CONJ, s_conj_s.get())) {
            if (auto s_child = parse_S()) {
                s_conj_s->add_child(std::move(s_child));
                s_node = std::move(s_conj_s);
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_tag_question = std::make_unique<ParseNode>();
        s_tag_question->label = "S";
        s_tag_question->type = NodeType::NON_TERMINAL;
        if (auto np1 = parse_NP()) {
            s_tag_question->add_child(std::move(np1));
            if (auto vp = parse_VP()) {
                s_tag_question->add_child(std::move(vp));
                if (consume(POS::AUX, s_tag_question.get())) {
                    if (auto np2 = parse_NP()) {
                        s_tag_question->add_child(std::move(np2));
                        s_node = std::move(s_tag_question);
                    }
                }
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_np_vp_conj_np = std::make_unique<ParseNode>();
        s_np_vp_conj_np->label = "S";
        s_np_vp_conj_np->type = NodeType::NON_TERMINAL;
        if (auto np1 = parse_NP()) {
            s_np_vp_conj_np->add_child(std::move(np1));
            if (auto vp = parse_VP()) {
                s_np_vp_conj_np->add_child(std::move(vp));
                if (consume(POS::CONJ, s_np_vp_conj_np.get())) {
                    if (auto np2 = parse_NP()) {
                        s_np_vp_conj_np->add_child(std::move(np2));
                        s_node = std::move(s_np_vp_conj_np);
                    }
                }
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_np_aux = std::make_unique<ParseNode>();
        s_np_aux->label = "S";
        s_np_aux->type = NodeType::NON_TERMINAL;
        if (auto np1 = parse_NP()) {
            s_np_aux->add_child(std::move(np1));
            if (consume(POS::AUX, s_np_aux.get())) {
                if (auto np2 = parse_NP()) {
                    s_np_aux->add_child(std::move(np2));
                    if (auto vp = parse_VP()) {
                        s_np_aux->add_child(std::move(vp));
                        s_node = std::move(s_np_aux);
                    }
                }
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_aux = std::make_unique<ParseNode>();
        s_aux->label = "S";
        s_aux->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, s_aux.get())) {
            if (auto np = parse_NP()) {
                s_aux->add_child(std::move(np));
                if (auto vp = parse_VP()) {
                    s_aux->add_child(std::move(vp));
                    s_node = std::move(s_aux);
                }
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    // S -> AUX NP NP (Handles copula questions like "Is that a cat")
    {
        auto s_aux_np_np = std::make_unique<ParseNode>();
        s_aux_np_np->label = "S";
        s_aux_np_np->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, s_aux_np_np.get())) {
            if (auto np1 = parse_NP()) {
                s_aux_np_np->add_child(std::move(np1));
                if (auto np2 = parse_NP()) {
                    s_aux_np_np->add_child(std::move(np2));
                    s_node = std::move(s_aux_np_np);
                }
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_np = std::make_unique<ParseNode>();
        s_np->label = "S";
        s_np->type = NodeType::NON_TERMINAL;
        if (auto np = parse_NP()) {
            s_np->add_child(std::move(np));
            s_node = std::move(s_np);
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_vp = std::make_unique<ParseNode>();
        s_vp->label = "S";
        s_vp->type = NodeType::NON_TERMINAL;
        if (auto vp = parse_VP()) {
            s_vp->add_child(std::move(vp));
            s_node = std::move(s_vp);
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_intj_s = std::make_unique<ParseNode>();
        s_intj_s->label = "S";
        s_intj_s->type = NodeType::NON_TERMINAL;
        if (consume(POS::INTJ, s_intj_s.get())) {
            if (auto s = parse_S()) {
                s_intj_s->add_child(std::move(s));
                s_node = std::move(s_intj_s);
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s_intj_np_adv = std::make_unique<ParseNode>();
        s_intj_np_adv->label = "S";
        s_intj_np_adv->type = NodeType::NON_TERMINAL;
        if (consume(POS::INTJ, s_intj_np_adv.get())) {
            if (auto np = parse_NP()) {
                s_intj_np_adv->add_child(std::move(np));
                if (consume(POS::ADV, s_intj_np_adv.get())) {
                    s_node = std::move(s_intj_np_adv);
                }
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s3 = std::make_unique<ParseNode>();
        s3->label = "S";
        s3->type = NodeType::NON_TERMINAL;
        if (consume(POS::INTJ, s3.get())) {
            if (auto np = parse_NP()) {
                s3->add_child(std::move(np));
                s_node = std::move(s3);
            }
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    {
        auto s4 = std::make_unique<ParseNode>();
        s4->label = "S";
        s4->type = NodeType::NON_TERMINAL;
        if (consume(POS::INTJ, s4.get())) {
            s_node = std::move(s4);
        }
        if (s_node) goto post_process;
        cursor_ = saved_cursor;
    }

    return nullptr;

post_process:
    if (s_node) {
        bool matched = true;
        while (matched) {
            if (auto extra_pp = parse_PP()) {
                auto wrapped = std::make_unique<ParseNode>();
                wrapped->label = "S";
                wrapped->type = NodeType::NON_TERMINAL;
                wrapped->add_child(std::move(s_node));
                wrapped->add_child(std::move(extra_pp));
                s_node = std::move(wrapped);
            } else if (current().tag == POS::ADV) {
                auto leaf = std::make_unique<ParseNode>();
                leaf->label = "ADV";
                leaf->lexeme = current().word;
                leaf->type = NodeType::TERMINAL;
                cursor_++;
                auto wrapped = std::make_unique<ParseNode>();
                wrapped->label = "S";
                wrapped->type = NodeType::NON_TERMINAL;
                wrapped->add_child(std::move(s_node));
                wrapped->add_child(std::move(leaf));
                s_node = std::move(wrapped);
            } else if (auto extra_s = parse_S()) {
                auto wrapped = std::make_unique<ParseNode>();
                wrapped->label = "S";
                wrapped->type = NodeType::NON_TERMINAL;
                wrapped->add_child(std::move(s_node));
                wrapped->add_child(std::move(extra_s));
                s_node = std::move(wrapped);
            } else {
                matched = false;
            }
        }
        return s_node;
    }
    
    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_S_base() {
    size_t saved_cursor = cursor_;
    std::unique_ptr<ParseNode> s_node = nullptr;

    if (auto np = parse_NP()) {
        if (auto vp = parse_VP()) {
            s_node = std::make_unique<ParseNode>();
            s_node->label = "S"; s_node->type = NodeType::NON_TERMINAL;
            s_node->add_child(std::move(np));
            s_node->add_child(std::move(vp));
            return s_node;
        }
    }
    cursor_ = saved_cursor;
    if (auto vp = parse_VP()) {
        s_node = std::make_unique<ParseNode>();
        s_node->label = "S"; s_node->type = NodeType::NON_TERMINAL;
        s_node->add_child(std::move(vp));
        return s_node;
    }
    cursor_ = saved_cursor;
    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_NP() {
    size_t saved_cursor = cursor_;

    // 1. RELATIVE CLAUSE: NP -> NP REL_PRO S
    // Try to match a base NP first, then see if a relative clause follows.
    // To avoid infinite recursion, we try the non-recursive patterns first.

    // 1. Base NP patterns (from longest to shortest)
    auto n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;
    
    // PRON (Rel Pro support)
    if (current().tag == POS::PRON && (current().word == "who" || current().word == "that" || current().word == "which")) {
        // Only return nullptr if we're not inside a recursive call that expects an NP
        // But parse_NP is the entry point.
    }

    // DET NUM ADJ N
    if (consume(POS::DET, n.get()) && consume(POS::NUM, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET ADJ ADJ N
    if (consume(POS::DET, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET V N N
    if (consume(POS::DET, n.get()) && consume(POS::V, n.get()) && consume(POS::N, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET ADJ N
    if (consume(POS::DET, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET NUM N
    if (consume(POS::DET, n.get()) && consume(POS::NUM, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET DET N
    if (consume(POS::DET, n.get()) && consume(POS::DET, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // NUM ADJ N
    if (consume(POS::NUM, n.get()) && consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET N
    if (consume(POS::DET, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // ADJ N
    if (consume(POS::ADJ, n.get()) && consume(POS::N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // DET PROPER_N
    if (consume(POS::DET, n.get()) && consume(POS::PROPER_N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // PRON
    if (consume(POS::PRON, n.get())) {
        // If we consumed "who/that" as a standalone PRON, we need to check if it's the start of a Rel Clause
        // But usually "who" is a Rel Clause start. 
        // Let's allow it as a standalone NP (for "Who is he?") but also check for extras.
        goto check_extra;
    }
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // PROPER_N
    if (consume(POS::PROPER_N, n.get())) goto check_extra;
    cursor_ = saved_cursor; n = std::make_unique<ParseNode>(); n->label = "NP"; n->type = NodeType::NON_TERMINAL;

    // N
    if (consume(POS::N, n.get())) goto check_extra;
    
    return nullptr;

check_extra:
    bool matched = true;
    while (matched) {
        size_t cp = cursor_;
        if (auto pp = parse_PP()) {
            auto wrap = std::make_unique<ParseNode>(); wrap->label = "NP"; wrap->type = NodeType::NON_TERMINAL;
            wrap->add_child(std::move(n)); wrap->add_child(std::move(pp)); n = std::move(wrap);
        } else if (current().tag == POS::PRON && (current().word == "who" || current().word == "that" || current().word == "which")) {
            // Relative clause: NP -> NP PRON S
            auto rel_pron = std::make_unique<ParseNode>();
            rel_pron->label = "PRON"; rel_pron->lexeme = current().word; rel_pron->type = NodeType::TERMINAL;
            cursor_++;
            
            // Try NP -> NP PRON S (e.g., "the cheese that the mouse stole")
            if (auto s = parse_S()) {
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "NP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(n)); wrap->add_child(std::move(rel_pron)); wrap->add_child(std::move(s));
                n = std::move(wrap);
            } else {
                cursor_ = cp + 1; // rewind to just after PRON
                // Try NP -> NP PRON VP (e.g., "the cat that chased the mouse")
                if (auto vp = parse_VP()) {
                    auto wrap = std::make_unique<ParseNode>(); wrap->label = "NP"; wrap->type = NodeType::NON_TERMINAL;
                    wrap->add_child(std::move(n)); wrap->add_child(std::move(rel_pron)); wrap->add_child(std::move(vp));
                    n = std::move(wrap);
                } else {
                    cursor_ = cp; 
                    matched = false;
                }
            }
        } else if (current().tag == POS::CONJ && (current().word == "and" || current().word == "or")) {
            // NP list/conjunction: NP -> NP CONJ NP
            auto conj = std::make_unique<ParseNode>();
            conj->label = "CONJ"; conj->lexeme = current().word; conj->type = NodeType::TERMINAL;
            cursor_++;
            if (auto next_np = parse_NP()) {
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "NP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(n)); wrap->add_child(std::move(conj)); wrap->add_child(std::move(next_np));
                n = std::move(wrap);
            } else { cursor_ = cp; matched = false; }
        } else { matched = false; }
    }
    return n;
}

std::unique_ptr<ParseNode> TopDownParser::parse_VP() {
    size_t saved_cursor = cursor_;
    std::unique_ptr<ParseNode> vp_node = nullptr;

    // 1. AUX + chain (will have been waiting)
    {
        auto v = std::make_unique<ParseNode>(); v->label = "VP"; v->type = NodeType::NON_TERMINAL;
        if (consume(POS::AUX, v.get())) {
            size_t checkpoint = cursor_;
            if (auto child = parse_VP()) { v->add_child(std::move(child)); vp_node = std::move(v); goto finalize; }
            cursor_ = checkpoint;
            if (consume(POS::ADJ, v.get())) { vp_node = std::move(v); goto finalize; }
            cursor_ = checkpoint;
            if (auto np = parse_NP()) { v->add_child(std::move(np)); vp_node = std::move(v); goto finalize; }
            cursor_ = checkpoint;
            vp_node = std::move(v); goto finalize;
        }
    }

    // 2. ADJ (happy)
    {
        auto v = std::make_unique<ParseNode>(); v->label = "VP"; v->type = NodeType::NON_TERMINAL;
        if (consume(POS::ADJ, v.get())) { vp_node = std::move(v); goto finalize; }
    }

    // 3. PREP + VP (to give)
    {
        auto v = std::make_unique<ParseNode>(); v->label = "VP"; v->type = NodeType::NON_TERMINAL;
        if (consume(POS::PREP, v.get())) {
            if (auto child = parse_VP()) { v->add_child(std::move(child)); vp_node = std::move(v); goto finalize; }
        }
    }

    // 4. V + chain (wants to give / give food)
    {
        auto v = std::make_unique<ParseNode>(); v->label = "VP"; v->type = NodeType::NON_TERMINAL;
        if (consume(POS::V, v.get())) {
            size_t checkpoint = cursor_;
            // V + NP + NP (give students grades)
            if (auto np1 = parse_NP()) {
                v->add_child(std::move(np1));
                size_t checkpoint2 = cursor_;
                if (auto np2 = parse_NP()) { v->add_child(std::move(np2)); vp_node = std::move(v); goto finalize; }
                else { cursor_ = checkpoint2; vp_node = std::move(v); goto finalize; } // VP -> V NP
            }
            cursor_ = checkpoint;
            // V + PREP + VP (to give)
            if (consume(POS::PREP, v.get())) {
                size_t checkpoint2 = cursor_;
                if (auto child = parse_VP()) { v->add_child(std::move(child)); vp_node = std::move(v); goto finalize; }
                else cursor_ = checkpoint;
            }
            cursor_ = checkpoint;
            vp_node = std::move(v); goto finalize; // VP -> V
        }
    }

finalize:
    if (vp_node) {
        bool matched = true;
        while (matched) {
            size_t cp = cursor_;
            if (auto pp = parse_PP()) {
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "VP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(vp_node)); wrap->add_child(std::move(pp)); vp_node = std::move(wrap);
            } else if (current().tag == POS::ADV) {
                auto leaf = std::make_unique<ParseNode>(); leaf->label = "ADV"; leaf->lexeme = current().word; leaf->type = NodeType::TERMINAL; cursor_++;
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "VP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(vp_node)); wrap->add_child(std::move(leaf)); vp_node = std::move(wrap);
            } else if (current().tag == POS::ADJ) {
                // VP -> VP ADJ (is tall)
                auto leaf = std::make_unique<ParseNode>(); leaf->label = "ADJ"; leaf->lexeme = current().word; leaf->type = NodeType::TERMINAL; cursor_++;
                auto wrap = std::make_unique<ParseNode>(); wrap->label = "VP"; wrap->type = NodeType::NON_TERMINAL;
                wrap->add_child(std::move(vp_node)); wrap->add_child(std::move(leaf)); vp_node = std::move(wrap);
            } else { matched = false; }
        }
    }
    // If we didn't match a VP but there's an ADV, try VP -> ADV VP
    if (!vp_node) {
        cursor_ = saved_cursor;
        if (current().tag == POS::ADV) {
            auto leaf = std::make_unique<ParseNode>(); leaf->label = "ADV"; leaf->lexeme = current().word; leaf->type = NodeType::TERMINAL; cursor_++;
            if (auto sub_vp = parse_VP()) {
                vp_node = std::make_unique<ParseNode>();
                vp_node->label = "VP"; vp_node->type = NodeType::NON_TERMINAL;
                vp_node->add_child(std::move(leaf));
                vp_node->add_child(std::move(sub_vp));
            } else { cursor_ = saved_cursor; }
        }
    }
    return vp_node;
}

std::unique_ptr<ParseNode> TopDownParser::parse_PP() {
    size_t saved_cursor = cursor_;

    auto pp = std::make_unique<ParseNode>();
    pp->label = "PP";
    pp->type = NodeType::NON_TERMINAL;
    
    if (consume(POS::PREP, pp.get())) {
        if (auto np = parse_NP()) {
            pp->add_child(std::move(np));
            return pp;
        }
    }
    
    cursor_ = saved_cursor;
    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_EXPR() {
    size_t saved_cursor = cursor_;
    auto expr = std::make_unique<ParseNode>();
    expr->label = "EXPR";
    expr->type = NodeType::NON_TERMINAL;

    if (auto term = parse_TERM()) {
        expr->add_child(std::move(term));

        while (current().word == "+" || current().word == "-") {
            auto op = std::make_unique<ParseNode>();
            op->label = "OP";
            op->lexeme = current().word;
            op->type = NodeType::TERMINAL;
            cursor_++;
            expr->add_child(std::move(op));

            if (auto next_term = parse_TERM()) {
                expr->add_child(std::move(next_term));
            } else {
                cursor_ = saved_cursor;
                return nullptr;
            }
        }
        return expr;
    }

    cursor_ = saved_cursor;
    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_TERM() {
    size_t saved_cursor = cursor_;
    auto term = std::make_unique<ParseNode>();
    term->label = "TERM";
    term->type = NodeType::NON_TERMINAL;

    if (auto factor = parse_FACTOR()) {
        term->add_child(std::move(factor));

        while (current().word == "*" || current().word == "/") {
            auto op = std::make_unique<ParseNode>();
            op->label = "OP";
            op->lexeme = current().word;
            op->type = NodeType::TERMINAL;
            cursor_++;
            term->add_child(std::move(op));

            if (auto next_factor = parse_FACTOR()) {
                term->add_child(std::move(next_factor));
            } else {
                cursor_ = saved_cursor;
                return nullptr;
            }
        }
        return term;
    }

    cursor_ = saved_cursor;
    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_FACTOR() {
    size_t saved_cursor = cursor_;
    auto factor = std::make_unique<ParseNode>();
    factor->label = "FACTOR";
    factor->type = NodeType::NON_TERMINAL;

    if (consume(POS::NUM, factor.get())) {
        return factor;
    }

    cursor_ = saved_cursor;
    if (consume(POS::LPAREN, factor.get())) {
        if (auto expr = parse_EXPR()) {
            factor->add_child(std::move(expr));
            if (consume(POS::RPAREN, factor.get())) {
                return factor;
            }
        }
    }

    cursor_ = saved_cursor;
    return nullptr;
}

```

## File: `README.md`

```markdown
# C++17 English Parse Tree Compiler

## Overview
This project is a custom compiler built in C++17 that analyzes and parses English sentences and basic arithmetic expressions. It processes raw string input through a lexical analyzer, constructs an Abstract Syntax Tree (AST) using either Top-Down or Bottom-Up parsing strategies, and visually renders the resulting parse tree directly in the terminal as a 2D ASCII structure. For English sentences, it also generates a structured Symbol Table that categorizes words by their part of speech and grammatical role. Furthermore, it supports generating Graphviz DOT files to render the trees graphically.

## Features
- **Lexical Analysis**: Custom tokenizer that categorizes words into Parts of Speech (POS) using a built-in dictionary and fallback suffix heuristics (e.g., "-ing", "-ly", "-ed").
- **Top-Down Parsing**: A Recursive Descent parser that processes Context-Free Grammar (CFG) rules with backtracking.
- **Bottom-Up Parsing**: A Shift-Reduce parser implementation utilizing a custom 1-token lookahead to resolve shift/reduce conflicts.
- **Terminal AST Visualization**: Renders the Abstract Syntax Tree in a highly-structured 2D ASCII format directly in the terminal using standard box-drawing characters.
- **Graphical AST Export**: Outputs parse trees into the Graphviz DOT format (`--dot`) for generating PNG, SVG, or PDF images.
- **Symbol Table Generation**: Performs a post-parse traversal of the AST to extract lexical scopes, grammar roles (e.g., NP.head, VP.auxiliary), and POS tags, presented in a formatted ASCII table.
- **Arithmetic Expressions**: Supports parsing standard math expressions (addition, subtraction, multiplication, division, and parentheses) honoring standard operator precedence.

## Requirements
- C++17 compatible compiler (e.g., g++, clang++)
- Bash (for running test scripts)
- (Optional) Graphviz installed for rendering `.dot` graphical outputs.

## Build Instructions
To compile the project from the source code, run the following command in the project root directory:

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o english-parser
```

## Usage
The compiled executable takes a string as input and parses it using the Top-Down parser by default.

### Top-Down Parsing (Default)
```bash
./english-parser "The quick brown fox jumps over the lazy dog"
```

### Bottom-Up Parsing
Use the `--bottom-up` flag to force the parser to use the Shift-Reduce strategy.
```bash
./english-parser --bottom-up "A man is holding a book"
```

### Graphical Export (Graphviz DOT)
Use the `--dot` flag followed by a filename to export the parse tree for graphical rendering. 
```bash
./english-parser --dot tree.dot "The quick brown fox jumps over the lazy dog"
dot -Tpng tree.dot -o tree.png
```

### Arithmetic Expressions
Math expressions are evaluated using the Top-Down parser. Note that the symbol table is automatically suppressed for mathematical inputs.
```bash
./english-parser "10 - 2 + 5 * (3 + 4)"
```

## Supported Grammar

### English Sentences
- **Contractions**: The Lexer naturally handles common contractions (e.g., "won't", "shouldn't", "can't") by stripping apostrophes during tokenization and resolving them to their base auxiliary tags via the dictionary.
- S -> NP VP | S PP | S ADV | NP VP PP | INTJ S | INTJ NP ADV | INTJ NP | INTJ | NP AUX NP VP | AUX NP VP | VP | CONJ S S | NP VP CONJ NP | NP VP AUX NP | ADV S | AUX NP NP | S S
- NP -> N N N | DET N N N | DET ADJ ADJ N | DET N N | N N | DET ADJ N | DET NUM N | DET N | NUM ADJ N | NUM N | ADJ ADJ N | ADJ N | ADJ V | DET V N N | DET V N | V N | V | PRON | PROPER_N | N | DET DET N
- VP -> AUX V NP ADV | VP PP | AUX V NP PP | AUX V NP | AUX V PP | AUX V ADV | AUX ADV V | AUX V | AUX NP PP | AUX NP ADV | AUX NP | AUX PP | AUX ADJ | AUX VP | V NP PP | V NP ADV | V NP | V PP | V ADV | V | AUX ADV | AUX PREP VP | V PREP VP | AUX NP NP | V NP NP
- PP -> PREP NP

### Arithmetic Expressions
- EXPR -> TERM (OP TERM)*
- TERM -> FACTOR (OP FACTOR)*
- FACTOR -> NUM | LPAREN EXPR RPAREN

## Project Structure
- `docs/`: Extensive project documentation, specifications, and roadmap details.
- `include/`: Header files defining classes and data structures (`lexer.h`, `top_down_parser.h`, etc.).
- `src/`: Implementation files for the Lexer, Parsers, AST Nodes, and Display utilities.
- `scripts/`: Execution scripts like `run_smoke_tests`.
- `tests/`: Unit tests and fixture files for verifying parser integrity.

```

## File: `justfile`

```text
# https://just.systems

default:
    echo 'Hello, world!'

build:
    echo 'Building the project...'
    g++ -std=c++17 src/*.cpp -Iinclude -o english-parser

```
