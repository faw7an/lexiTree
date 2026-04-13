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
│   ├── display.cpp
│   ├── lexer.cpp
│   ├── main.cpp
│   ├── parse_tree.cpp
│   ├── pos_dict.cpp
│   ├── symbol_table.cpp
│   └── top_down_parser.cpp
├── tests/
│   ├── fixtures/
│   │   └── sentences.txt
│   ├── test_bottom_up.cpp
│   ├── test_display.cpp
│   ├── test_lexer.cpp
│   ├── test_symbol_table.cpp
│   └── test_top_down.cpp
├── README.md
├── justfile
├── patch_debug
├── update_bottom_up.patch
└── update_top_down.patch
```

# Project Files

## File: `data/dictionary.txt`

```text
# English POS Dictionary for Parser
# Format: word TAG
# Tags: DET N V ADJ ADV PREP PRON CONJ AUX NUM PROPER_N INTJ
# Unknown/new words (names, places, slang) default to N at runtime.
# Add custom words at the bottom of this file.
#

# ── DET (determiners) ──
a DET
all DET
an DET
any DET
both DET
each DET
either DET
enough DET
every DET
few DET
half DET
her DET
his DET
its DET
least DET
less DET
little DET
many DET
more DET
most DET
much DET
my DET
neither DET
no DET
other DET
our DET
several DET
some DET
such DET
that DET
the DET
their DET
these DET
this DET
those DET
whosever DET
your DET
zero DET

# ── PRON (pronouns) ──
another PRON
anyone PRON
anything PRON
anywhere PRON
each other PRON
everybody PRON
everyone PRON
everything PRON
everywhere PRON
he PRON
here ADV
hers PRON
herself PRON
him PRON
himself PRON
i PRON
it PRON
itself PRON
me PRON
mine PRON
myself PRON
no one PRON
nobody PRON
nothing PRON
nowhere PRON
one PRON
one another PRON
ones PRON
others PRON
ours PRON
ourselves PRON
she PRON
somebody PRON
someone PRON
something PRON
somewhere PRON
theirs PRON
them PRON
themselves PRON
there ADV
they PRON
u PRON
us PRON
we PRON
what PRON
whatever PRON
which PRON
whichever PRON
who PRON
whoever PRON
whom PRON
whomever PRON
whose PRON
you PRON
yours PRON
yourself PRON
yourselves PRON

# ── AUX (auxiliaries) ──
aint AUX
am AUX
are AUX
arent AUX
be AUX
been AUX
being AUX
can AUX
cant AUX
could AUX
couldnt AUX
dare AUX
did AUX
didnt AUX
do AUX
does AUX
doesnt AUX
doing AUX
done AUX
had AUX
hadnt AUX
has AUX
hasnt AUX
have AUX
havent AUX
having AUX
is AUX
isnt AUX
may AUX
might AUX
must AUX
mustnt AUX
ought AUX
shall AUX
should AUX
shouldnt AUX
was AUX
wasnt AUX
were AUX
werent AUX
will AUX
wont AUX
would AUX
wouldnt AUX

# ── PREP (prepositions) ──
aboard PREP
about PREP
above PREP
across PREP
against PREP
along PREP
amid PREP
amidst PREP
among PREP
amongst PREP
around PREP
aside PREP
at PREP
atop PREP
behind PREP
below PREP
beneath PREP
beside PREP
between PREP
beyond PREP
by PREP
concerning PREP
despite PREP
down PREP
during PREP
except PREP
excluding PREP
from PREP
in PREP
inside PREP
into PREP
like PREP
minus PREP
near PREP
nearby PREP
notwithstanding PREP
of PREP
off PREP
on PREP
onto PREP
opposite PREP
out PREP
outside PREP
over PREP
past PREP
pending PREP
per PREP
plus PREP
regarding PREP
through PREP
throughout PREP
to PREP
toward PREP
towards PREP
under PREP
underneath PREP
unlike PREP
unto PREP
up PREP
upon PREP
versus PREP
via PREP
vs PREP
with PREP
within PREP
without PREP
worth PREP

# ── CONJ (conjunctions) ──
accordingly CONJ
additionally CONJ
after CONJ
alternatively CONJ
although CONJ
and CONJ
as CONJ
as long as CONJ
as soon as CONJ
assuming CONJ
because CONJ
before CONJ
besides CONJ
but CONJ
consequently CONJ
even CONJ
even if CONJ
even though CONJ
eventually CONJ
finally CONJ
for CONJ
furthermore CONJ
hence CONJ
however CONJ
if CONJ
in case CONJ
in order that CONJ
instead CONJ
lest CONJ
meanwhile CONJ
moreover CONJ
nevertheless CONJ
nonetheless CONJ
nor CONJ
now CONJ
now that CONJ
once CONJ
or CONJ
otherwise CONJ
overall CONJ
provided CONJ
rather than CONJ
since CONJ
so CONJ
so that CONJ
such that CONJ
than CONJ
thereby CONJ
therefore CONJ
thereof CONJ
though CONJ
thus CONJ
unless CONJ
until CONJ
when CONJ
whenever CONJ
where CONJ
whereas CONJ
whereby CONJ
wherein CONJ
wherever CONJ
whether CONJ
while CONJ
yet CONJ

# ── NUM (numbers) ──
billion NUM
dozen NUM
eight NUM
eighteen NUM
eighth NUM
eighty NUM
eleven NUM
eleventh NUM
fifteen NUM
fifth NUM
fifty NUM
five NUM
forty NUM
four NUM
fourteen NUM
fourth NUM
hundred NUM
million NUM
nine NUM
nineteen NUM
ninety NUM
ninth NUM
quarter NUM
seven NUM
seventeen NUM
seventh NUM
seventy NUM
six NUM
sixteen NUM
sixth NUM
sixty NUM
ten NUM
tenth NUM
third NUM
thirteen NUM
thirty NUM
thousand NUM
three NUM
trillion NUM
twelfth NUM
twelve NUM
twenty NUM
twice NUM
two NUM

# ── INTJ (interjections) ──
absolutely INTJ
ah INTJ
alas INTJ
apparently INTJ
basically INTJ
bye INTJ
certainly INTJ
clearly INTJ
definitely INTJ
exactly INTJ
frankly INTJ
hello INTJ
hey INTJ
hi INTJ
hmm INTJ
honestly INTJ
hooray INTJ
hopefully INTJ
huh INTJ
hurray INTJ
indeed INTJ
just INTJ
literally INTJ
merely INTJ
nope INTJ
obviously INTJ
oh INTJ
ok INTJ
okay INTJ
ooh INTJ
oops INTJ
ouch INTJ
really INTJ
right INTJ
seriously INTJ
simply INTJ
sure INTJ
thankfully INTJ
ugh INTJ
unfortunately INTJ
well INTJ
whoa INTJ
wow INTJ
yay INTJ
yeah INTJ
yep INTJ

# ── V (verbs) ──
accept V
accepted V
accepting V
accepts V
achieve V
achieveed V
achieveing V
achieves V
add V
added V
adding V
adds V
admire V
admired V
admires V
admiring V
advise V
adviseed V
adviseing V
advises V
affect V
affected V
affecting V
affects V
agree V
agreed V
agreeed V
agreeing V
agrees V
allow V
allowed V
allowing V
allows V
analyze V
analyzeed V
analyzeing V
analyzes V
announce V
announceed V
announceing V
announces V
answered V
answering V
apologize V
apologizeed V
apologizeing V
apologizes V
appear V
appeared V
appearing V
appears V
argue V
argueed V
argueing V
argues V
arrive V
arriveed V
arriveing V
arrives V
ask V
asked V
asking V
asks V
assume V
assumed V
assumes V
ate V
attach V
attached V
attaching V
attachs V
attack V
attacked V
attacking V
attacks V
attend V
attended V
attending V
attends V
bake V
bakeed V
bakeing V
bakes V
beat V
beaten V
beating V
beats V
became V
become V
becomes V
becoming V
beg V
began V
beged V
begin V
beging V
beginning V
begins V
begs V
begun V
believe V
believed V
believeed V
believeing V
believes V
believing V
belong V
belonged V
belonging V
belongs V
bend V
bending V
bends V
bent V
bit V
bite V
bites V
biting V
bitten V
blame V
blameed V
blameing V
blames V
blew V
block V
blocked V
blocking V
blocks V
blow V
blowing V
blown V
blows V
bought V
break V
breaked V
breaking V
breaks V
breathe V
breatheed V
breatheing V
breathes V
bring V
bringing V
brings V
broke V
broken V
brought V
build V
builded V
building V
builds V
built V
buy V
buying V
buys V
calculate V
calculateed V
calculateing V
calculates V
call V
called V
calling V
calls V
came V
care V
careed V
careing V
cares V
carried V
carries V
carry V
carrying V
catch V
catches V
catching V
caught V
causeed V
causeing V
change V
changed V
changeed V
changeing V
changes V
changing V
check V
checked V
checking V
checks V
choose V
chooses V
choosing V
chose V
chosen V
claim V
claimed V
claiming V
claims V
cleaned V
cleaning V
cleans V
climb V
climbed V
climbing V
climbs V
close V
closed V
closes V
closing V
collect V
collected V
collecting V
collects V
colored V
coloring V
colors V
colour V
coloured V
colouring V
combine V
combined V
combines V
combining V
come V
comes V
coming V
compare V
compareed V
compareing V
compares V
complain V
complained V
complaining V
complains V
completeed V
completeing V
completes V
confirm V
confirmed V
confirming V
confirms V
connect V
connected V
connecting V
connects V
consider V
considered V
considering V
considers V
construct V
constructed V
constructing V
constructs V
contain V
contained V
containing V
contains V
continue V
continued V
continueed V
continueing V
continues V
continuing V
control V
controled V
controling V
controlled V
controlling V
controls V
cook V
cooked V
cooking V
cooks V
cooled V
cooling V
cools V
copy V
copyed V
copying V
copys V
count V
counted V
counting V
counts V
crawl V
crawled V
crawling V
crawls V
create V
created V
creates V
creating V
creep V
creeping V
creeps V
crept V
cried V
cries V
criticize V
criticizeed V
criticizeing V
criticizes V
cross V
crossed V
crossing V
crosss V
cry V
crying V
cut V
cuted V
cuting V
cuts V
cutted V
cutting V
dance V
danced V
danceed V
danceing V
dances V
dancing V
deal V
dealing V
deals V
dealt V
decide V
decided V
decides V
deciding V
declare V
declareed V
declareing V
declares V
decrease V
decreased V
decreaseed V
decreaseing V
decreases V
decreasing V
defend V
defended V
defending V
defends V
delete V
deleteed V
deleteing V
deletes V
demand V
demanded V
demanding V
demands V
deny V
denyed V
denying V
denys V
depend V
depended V
depending V
depends V
describe V
described V
describeed V
describeing V
describes V
describing V
deserve V
deserveed V
deserveing V
deserves V
design V
designed V
designing V
designs V
destroy V
destroyed V
destroying V
destroys V
detect V
detected V
detecting V
detects V
develop V
developed V
developing V
develops V
direct V
directed V
directing V
directs V
disagree V
disagreeed V
disagreeing V
disagrees V
discover V
discovered V
discovering V
discovers V
discuss V
discussed V
discussing V
discusss V
distribute V
distributeed V
distributeing V
distributes V
divide V
divided V
divides V
dividing V
doubt V
doubted V
doubting V
doubts V
drank V
draw V
drawing V
drawn V
draws V
dressed V
dressing V
dresss V
drew V
drift V
drifted V
drifting V
drifts V
drink V
drinking V
drinks V
drive V
driveed V
driveing V
driven V
drives V
driving V
drop V
droped V
droping V
dropped V
dropping V
drops V
drove V
drunk V
earn V
earned V
earning V
earns V
eat V
eaten V
eating V
eats V
emptyed V
emptying V
emptys V
enable V
enableed V
enableing V
enables V
end V
ended V
ending V
ends V
enjoy V
enjoyed V
enjoying V
enjoys V
enter V
entered V
entering V
enters V
equal V
equaled V
equaling V
equals V
estimate V
estimateed V
estimateing V
estimates V
evaluate V
evaluateed V
evaluateing V
evaluates V
examine V
examineed V
examineing V
examines V
exclude V
excludeed V
excludeing V
excludes V
exist V
existed V
existing V
exists V
exit V
exited V
exiting V
exits V
expand V
expanded V
expanding V
expands V
expect V
expected V
expecting V
expects V
explain V
explained V
explaining V
explains V
extend V
extended V
extending V
extends V
fail V
failed V
failing V
fails V
fall V
fallen V
falling V
falls V
farm V
farmed V
farming V
farms V
feared V
fearing V
fears V
feed V
feeded V
feeding V
feeds V
feel V
feeled V
feeling V
feels V
fell V
felt V
fight V
fighting V
fights V
fill V
filled V
filling V
fills V
find V
finding V
finds V
finish V
finished V
finishes V
finishing V
finishs V
fit V
fits V
fitting V
fix V
fixing V
fixs V
flew V
flies V
float V
floated V
floating V
floats V
flow V
flowed V
flowing V
flown V
flows V
fly V
flying V
follow V
followed V
following V
follows V
forgave V
forget V
forgeted V
forgeting V
forgets V
forgetting V
forgive V
forgiveed V
forgiveing V
forgiven V
forgives V
forgiving V
forgot V
forgotten V
fought V
found V
freeze V
freezes V
freezing V
froze V
frozen V
gain V
gained V
gaining V
gains V
gather V
gathered V
gathering V
gathers V
gave V
gaze V
gazeed V
gazeing V
gazes V
generate V
generated V
generates V
generating V
get V
gets V
getting V
give V
given V
gives V
giving V
glance V
glanceed V
glanceing V
glances V
glide V
glided V
glides V
gliding V
glow V
glowed V
glowing V
glows V
go V
goes V
going V
gone V
got V
gotten V
grab V
grabed V
grabing V
grabs V
greet V
greeted V
greeting V
greets V
grew V
grow V
growed V
growing V
grown V
grows V
guess V
guessed V
guessing V
guesss V
guide V
guideed V
guideing V
guides V
happen V
happened V
happening V
happens V
harvest V
harvested V
harvesting V
harvests V
hated V
hates V
hating V
heal V
healed V
healing V
heals V
hear V
heard V
hearing V
hears V
heated V
heating V
heats V
held V
help V
helped V
helping V
helps V
hid V
hidden V
hide V
hides V
hiding V
hit V
hits V
hitted V
hitting V
hold V
holding V
holds V
hop V
hoped V
hopeed V
hopeing V
hopes V
hoping V
hops V
hunt V
hunted V
hunting V
hunts V
hurried V
hurries V
hurry V
hurrying V
imagine V
imagined V
imagineed V
imagineing V
imagines V
imagining V
improve V
improved V
improveed V
improveing V
improves V
improving V
include V
included V
includeed V
includeing V
includes V
including V
increase V
increased V
increaseed V
increaseing V
increases V
increasing V
influence V
influenceed V
influenceing V
influences V
inform V
informed V
informing V
informs V
inspire V
inspired V
inspires V
inspiring V
introduce V
introduceed V
introduceing V
introduces V
investigate V
investigateed V
investigateing V
investigates V
invite V
inviteed V
inviteing V
invites V
jog V
joged V
joging V
jogs V
join V
joined V
joining V
joins V
judgeed V
judgeing V
judges V
jump V
jumped V
jumping V
jumps V
keep V
keeped V
keeping V
keeps V
kept V
kick V
kicked V
kicking V
kicks V
kill V
killed V
killing V
kills V
kneel V
kneeling V
kneels V
knelt V
knew V
knit V
knits V
knitting V
know V
knowing V
known V
knows V
lack V
lacked V
lacking V
lacks V
laid V
lain V
last V
lasted V
lasting V
lasts V
laugh V
laughed V
laughing V
laughs V
lay V
laying V
lays V
lead V
leaded V
leading V
leads V
leap V
leaping V
leaps V
leapt V
learn V
learned V
learning V
learns V
leave V
leaved V
leaveed V
leaveing V
leaves V
leaving V
led V
left V
let V
lets V
letting V
lie V
lies V
lift V
lifted V
lifting V
lifts V
likeed V
likeing V
likes V
limit V
limiting V
limits V
link V
linked V
linking V
links V
listen V
listened V
listening V
listens V
live V
lived V
lives V
living V
look V
looked V
looking V
looks V
lose V
loses V
losing V
lost V
love V
loved V
loves V
loving V
lying V
made V
make V
makes V
making V
manage V
managed V
manageed V
manageing V
manages V
managing V
march V
marched V
marching V
marchs V
match V
matched V
matching V
matchs V
matter V
mattered V
mattering V
matters V
mean V
meaning V
means V
meant V
measure V
measureed V
measureing V
measures V
meet V
meeting V
meets V
memorize V
memorizeed V
memorizeing V
memorizes V
mention V
mentioned V
mentioning V
mentions V
merge V
mergeed V
mergeing V
merges V
met V
mind V
minded V
minding V
minds V
mix V
mixed V
mixing V
mixs V
move V
moved V
moves V
moving V
need V
needed V
needing V
needs V
notice V
noticed V
noticeed V
noticeing V
notices V
noticing V
notify V
notifyed V
notifying V
notifys V
observe V
observeed V
observeing V
observes V
occur V
occured V
occuring V
occurs V
open V
opened V
opening V
opens V
order V
ordered V
ordering V
orders V
organize V
organizeed V
organizeing V
organizes V
own V
owned V
owning V
owns V
paid V
paint V
painted V
painting V
paints V
pass V
passed V
passing V
passs V
paste V
pasteed V
pasteing V
pastes V
pay V
paying V
pays V
peek V
peeked V
peeking V
peeks V
persist V
persisted V
persisting V
persists V
pick V
picked V
picking V
picks V
placeed V
placeing V
places V
planed V
planing V
planted V
planting V
play V
played V
playing V
plays V
plead V
pleaded V
pleading V
pleads V
possess V
possessed V
possessing V
possesss V
post V
posted V
posting V
posts V
pour V
poured V
pouring V
pours V
practice V
practiced V
practiceed V
practiceing V
practices V
practicing V
praise V
praiseed V
praiseing V
praises V
prefer V
prefered V
prefering V
prefers V
prepare V
prepareed V
prepareing V
prepares V
press V
pressed V
pressing V
presss V
prevent V
prevented V
preventing V
prevents V
print V
printed V
printing V
prints V
produce V
produced V
produces V
producing V
promise V
promiseed V
promiseing V
promises V
protect V
protected V
protecting V
protects V
publish V
published V
publishing V
publishs V
pull V
pulled V
pulling V
pulls V
punch V
punched V
punching V
punchs V
push V
pushed V
pushes V
pushing V
pushs V
put V
puts V
putted V
putting V
questioned V
questioning V
quit V
quits V
quitting V
race V
raced V
races V
racing V
ran V
rang V
reach V
reached V
reaching V
reachs V
read V
readed V
reading V
reads V
realize V
realized V
realizeed V
realizeing V
realizes V
realizing V
recall V
recalled V
recalling V
recalls V
receive V
receiveed V
receiveing V
receives V
recognize V
recognized V
recognizeed V
recognizeing V
recognizes V
recognizing V
recommend V
recommended V
recommending V
recommends V
reduce V
reduceed V
reduceing V
reduces V
refuse V
refused V
refuseed V
refuseing V
refuses V
refusing V
reject V
rejecting V
rejects V
release V
releaseed V
releaseing V
releases V
rely V
relyed V
relying V
relys V
remain V
remained V
remaining V
remains V
remember V
remembered V
remembering V
remembers V
remind V
reminded V
reminding V
reminds V
remove V
removed V
removeed V
removeing V
removes V
removing V
repeat V
repeated V
repeating V
repeats V
reply V
replyed V
replying V
replys V
report V
reported V
reporting V
reports V
represent V
represented V
representing V
represents V
request V
requested V
requesting V
requests V
require V
required V
requireed V
requireing V
requires V
requiring V
rescue V
rescueed V
rescueing V
rescues V
research V
researched V
researching V
researchs V
reside V
resideed V
resideing V
resides V
respond V
responded V
responding V
responds V
rest V
rested V
resting V
restrict V
restricted V
restricting V
restricts V
rests V
result V
resulted V
resulting V
results V
return V
returned V
returning V
returns V
reveal V
revealed V
revealing V
reveals V
review V
reviewed V
reviewing V
reviews V
ridden V
ride V
rided V
rides V
riding V
ringing V
rings V
rise V
risen V
rises V
rising V
rode V
rose V
row V
rowed V
rowing V
rows V
run V
runed V
rung V
runing V
runned V
running V
runs V
rush V
rushed V
rushing V
rushs V
said V
sail V
sailed V
sailing V
sails V
sang V
sat V
save V
saveed V
saveing V
saves V
saw V
say V
saying V
says V
sealed V
search V
searched V
searching V
searchs V
see V
seeing V
seem V
seemed V
seeming V
seems V
seen V
sees V
sell V
selling V
sells V
send V
sended V
sending V
sends V
sense V
senseed V
senseing V
senses V
sent V
separate V
separateed V
separateing V
separates V
set V
sets V
setting V
shake V
shaked V
shaken V
shakes V
shaking V
share V
shareed V
shareing V
shares V
shine V
shines V
shining V
shone V
shook V
shoot V
shooting V
shoots V
shot V
shout V
shouted V
shouting V
shouts V
show V
showed V
showing V
shown V
shows V
shut V
shuts V
shutting V
sing V
singed V
singing V
sings V
sit V
sited V
siting V
sits V
sitted V
sitting V
skip V
skiped V
skiping V
skips V
sleep V
sleeping V
sleeps V
slept V
slice V
sliced V
slices V
slicing V
slid V
slide V
slides V
sliding V
smell V
smelled V
smelling V
smells V
smile V
smileed V
smileing V
smiles V
sold V
solve V
solveed V
solveing V
solves V
spat V
speak V
speaked V
speaking V
speaks V
spend V
spended V
spending V
spends V
spent V
spit V
spits V
spitting V
split V
splited V
spliting V
splits V
splitting V
spoke V
spoken V
spot V
spoted V
spoting V
spots V
sprang V
spread V
spreading V
spreads V
spring V
springs V
sprint V
sprinted V
sprinting V
sprints V
sprung V
squeeze V
squeezeed V
squeezeing V
squeezes V
stand V
standing V
stands V
stare V
stareed V
stareing V
stares V
start V
started V
starting V
starts V
stated V
stating V
stay V
stayed V
staying V
stays V
steal V
stealing V
steals V
sting V
stinging V
stings V
stir V
stired V
stiring V
stirs V
stole V
stolen V
stood V
stop V
stoped V
stoping V
stopped V
stopping V
stops V
strike V
strikes V
striking V
stroll V
strolled V
strolling V
strolls V
struck V
studied V
studies V
study V
studyed V
studying V
studys V
stung V
succeed V
succeeded V
succeeding V
succeeds V
suggest V
suggested V
suggesting V
suggests V
sung V
support V
supported V
supporting V
supports V
suppose V
supposed V
supposes V
supposing V
swam V
sweep V
sweeping V
sweeps V
swept V
swim V
swimed V
swiming V
swimming V
swims V
swing V
swinging V
swings V
swum V
swung V
take V
taked V
taken V
takes V
taking V
talk V
talked V
talking V
talks V
taste V
tasted V
tasteed V
tasteing V
tastes V
tasting V
taught V
teach V
teached V
teaches V
teaching V
teachs V
tell V
telling V
tells V
test V
tested V
testing V
tests V
thank V
thanked V
thanking V
thanks V
think V
thinking V
thinks V
thought V
threw V
throw V
throwing V
thrown V
throws V
tick V
ticked V
ticking V
ticks V
told V
took V
touch V
touched V
touches V
touching V
touchs V
trade V
tradeed V
tradeing V
trades V
train V
trained V
training V
trains V
transform V
transformed V
transforming V
transforms V
travel V
traveled V
traveling V
travels V
trip V
tripped V
tripping V
trips V
trust V
trusted V
trusting V
trusts V
turn V
turned V
turning V
turns V
typeed V
typeing V
types V
understand V
understanding V
understands V
understood V
update V
updateed V
updateing V
updates V
use V
used V
uses V
using V
viewed V
viewing V
views V
visit V
visited V
visiting V
visits V
wait V
waited V
waiting V
waits V
wake V
wakes V
waking V
walk V
walked V
walking V
walks V
wander V
wandered V
wandering V
wanders V
want V
wanted V
wanting V
wants V
warn V
warned V
warning V
warns V
wash V
washed V
washing V
washs V
watched V
watching V
watchs V
watered V
watering V
waters V
wear V
weared V
wearing V
wears V
weep V
weeping V
weeps V
welcome V
welcomeed V
welcomeing V
welcomes V
went V
wept V
whisper V
whispered V
whispering V
whispers V
win V
winning V
wins V
wish V
wished V
wishing V
wishs V
woke V
woken V
won V
wonder V
wondered V
wondering V
wonders V
wore V
work V
worked V
working V
works V
worn V
worries V
worry V
worrying V
write V
writeed V
writeing V
writes V
writing V
written V
wrote V

# ── N (nouns) ──
ability N
activist N
actor N
adult N
africa N
african N
afternoon N
agriculture N
air N
airport N
airports N
amount N
ancestor N
anger N
animal N
animals N
ankle N
ankles N
answer N
answers N
ant N
ants N
apartment N
apartments N
ape N
apes N
architect N
area N
arm N
arms N
arrow N
arrows N
art N
arteries N
artery N
artist N
asante N
ash N
aspect N
assignment N
astronaut N
athlete N
attitude N
aunt N
average N
baba N
baby N
bado N
bag N
bags N
ball N
balls N
baraza N
bay N
bays N
beach N
beaches N
bear N
bears N
beast N
beasts N
beauty N
bed N
beds N
bee N
beer N
bees N
behavior N
belly N
bike N
bikes N
bill N
bills N
bird N
birds N
blood N
board N
boat N
boats N
boma N
bone N
bones N
book N
books N
boss N
bottle N
bottles N
bow N
bowl N
bowls N
bows N
box N
boxes N
boy N
bracelet N
brain N
branch N
branches N
bread N
breakfast N
bridge N
bridges N
brother N
builder N
builders N
buildings N
bus N
buses N
business N
butterflies N
butterfly N
button N
buttons N
cable N
cables N
cake N
camera N
cameras N
campus N
captain N
car N
card N
cards N
cars N
case N
cases N
cash N
cat N
cats N
cause N
causes N
cave N
caves N
ceiling N
ceilings N
chai N
chain N
chains N
chair N
chairs N
champion N
chance N
character N
cheek N
chef N
chest N
chicken N
chickens N
chief N
child N
children N
chimpanzee N
chimpanzees N
chin N
choice N
church N
churches N
citizen N
class N
classmate N
cliff N
cliffs N
climate N
climber N
climbers N
clock N
clocks N
cloth N
cloud N
clouds N
coach N
coast N
coasts N
coat N
coffee N
coin N
coins N
collection N
college N
color N
colours N
community N
computer N
computers N
condition N
conditions N
connection N
connections N
consultant N
cooker N
cookie N
cookies N
cost N
costs N
country N
couple N
court N
courts N
cousin N
cow N
cows N
creature N
creatures N
criminal N
critic N
crocodile N
crocodiles N
crow N
crows N
culture N
cup N
cups N
currents N
dancer N
dancers N
darkness N
data N
daughter N
dawn N
day N
days N
death N
deer N
degree N
dentist N
depth N
descendant N
desert N
deserts N
designer N
desk N
desks N
detective N
developer N
development N
device N
devices N
dice N
difference N
differences N
dinner N
direction N
director N
dirt N
distance N
doctor N
dog N
dogs N
dolphin N
dolphins N
door N
doors N
dorm N
dream N
dreams N
dress N
driver N
drivers N
duck N
ducks N
dusk N
dust N
eagle N
eagles N
ear N
earring N
ears N
earth N
eastern N
economy N
editor N
education N
effect N
effects N
elbow N
elbows N
eldoret N
elephant N
elephants N
elk N
employee N
enemy N
engine N
engineer N
engines N
environment N
evening N
event N
events N
evil N
exam N
example N
examples N
experience N
experiences N
expert N
eye N
eyes N
fabric N
face N
fact N
factories N
factory N
failure N
family N
farmer N
farmers N
father N
fear N
feelings N
feet N
field N
fields N
finger N
fingers N
fire N
fish N
fisherman N
fishermen N
fishes N
flame N
floor N
floors N
flower N
flowers N
fog N
food N
foot N
forehead N
forest N
forests N
fork N
forks N
form N
fox N
foxes N
freedom N
friend N
frog N
frogs N
fruit N
fruits N
game N
games N
garden N
gardens N
garissa N
giraffe N
giraffes N
girl N
githeri N
glass N
glasses N
goal N
goals N
goat N
goats N
gold N
gorilla N
gorillas N
government N
grandchild N
grandfather N
grandmother N
grandparent N
grass N
ground N
group N
growth N
guard N
guest N
gun N
guns N
gym N
gyms N
hair N
hall N
hamster N
hamsters N
hand N
hands N
harambee N
harbor N
harbors N
hare N
hares N
hat N
hate N
hawk N
hawks N
head N
health N
heart N
heat N
heel N
heels N
height N
helicopter N
helicopters N
hen N
hens N
hero N
highway N
highways N
hill N
hills N
hip N
hippo N
hippos N
hips N
history N
home N
homes N
hope N
horse N
horses N
hospital N
hospitals N
host N
hostel N
hotel N
hotels N
hour N
hours N
house N
houses N
hunter N
hunters N
husband N
ice N
idea N
ideas N
immigrant N
improvement N
industry N
information N
ink N
insect N
insects N
iron N
island N
islands N
item N
items N
jacket N
jambo N
jaw N
joint N
joints N
journalist N
joy N
jua N
judge N
juice N
jungle N
jungles N
justice N
kakamega N
kalenjin N
kamba N
karibu N
kenya N
key N
keys N
kid N
kidney N
kidneys N
kikuyu N
king N
kisumu N
knee N
knees N
knife N
knives N
knowledge N
lake N
lakes N
lamp N
lamps N
land N
language N
laptop N
laptops N
law N
lawyer N
leader N
leaders N
leaf N
lecture N
lecturer N
leg N
legs N
length N
letter N
letters N
level N
libraries N
library N
life N
lightning N
line N
lines N
lion N
lions N
lip N
lips N
list N
listener N
listeners N
liver N
lizard N
lizards N
location N
lock N
locks N
loser N
luck N
luhya N
lunch N
lung N
lungs N
luo N
maasai N
machakos N
machine N
machines N
majority N
mama N
man N
manager N
managers N
mandazi N
mara N
market N
markets N
masai N
matatu N
meadow N
meadows N
meal N
meals N
meat N
medicine N
memories N
memory N
men N
message N
metal N
method N
methods N
mice N
middle N
midnight N
milk N
minister N
minority N
minute N
minutes N
mirror N
mirrors N
mist N
mmu N
mombasa N
moments N
money N
monkey N
monkeys N
month N
months N
moon N
moose N
morning N
mosque N
mosques N
mosquito N
mosquitoes N
mother N
motor N
motors N
mountain N
mountains N
mouse N
mouth N
mtoto N
mud N
muscle N
muscles N
museum N
museums N
music N
musician N
mzee N
nail N
nails N
nairobi N
nakuru N
name N
names N
nature N
ndugu N
neck N
necklace N
neighbor N
nephew N
nerve N
nerves N
news N
niece N
night N
noon N
northern N
nose N
notebook N
notebooks N
number N
numbers N
nurse N
nyanza N
object N
objects N
ocean N
oceans N
office N
officer N
offices N
oil N
opinion N
organization N
owl N
owls N
owner N
owners N
painter N
painters N
pants N
paper N
papers N
parent N
park N
parks N
parrot N
parrots N
part N
parts N
party N
path N
paths N
pattern N
patterns N
peace N
pebble N
pebbles N
pen N
pencil N
pencils N
penguin N
penguins N
pens N
people N
person N
personality N
pet N
pets N
pharmacist N
phone N
phones N
photographer N
piece N
pieces N
pig N
pigs N
pilot N
pipe N
pipes N
place N
plain N
plains N
plan N
plane N
planes N
planet N
planets N
plans N
plant N
plants N
plastic N
plate N
plateau N
plateaus N
plates N
player N
players N
point N
pole N
police N
politics N
pond N
ponds N
pool N
pools N
port N
ports N
position N
power N
president N
price N
prices N
prince N
princess N
principal N
problem N
problems N
process N
processes N
professor N
programmer N
progress N
project N
publisher N
pupil N
purpose N
purse N
quality N
quantity N
queen N
question N
questions N
rabbit N
rabbits N
radio N
radios N
rafiki N
rain N
range N
rat N
rats N
reader N
readers N
reason N
reasons N
refugee N
region N
registration N
relationship N
relationships N
relative N
religion N
reporter N
restaurant N
restaurants N
rib N
ribs N
rice N
rift N
ring N
river N
rivers N
road N
roads N
rock N
roof N
roofs N
rooster N
roosters N
root N
roots N
rope N
ropes N
runner N
runners N
sadness N
safari N
sailor N
salad N
salt N
sand N
savanna N
savannah N
sawa N
school N
schools N
science N
scientist N
screen N
screens N
sea N
seal N
seals N
seas N
second N
seconds N
seed N
seeds N
semester N
sentence N
sentences N
shadow N
shamba N
shape N
shapes N
shark N
sharks N
sheep N
ship N
ships N
shirt N
shirts N
shoes N
shop N
shops N
shore N
shores N
shoulder N
shoulders N
side N
sides N
sign N
signs N
similarities N
similarity N
singer N
singers N
sister N
situation N
situations N
size N
skill N
skin N
skull N
sky N
smoke N
snack N
snacks N
snake N
snakes N
snow N
society N
sofa N
sofas N
soil N
soldier N
solution N
solutions N
somali N
son N
soup N
sparrow N
sparrows N
speaker N
speakers N
specialist N
speed N
spice N
spices N
spider N
spiders N
spine N
spoon N
spoons N
squirrel N
squirrels N
stadium N
stadiums N
staff N
stage N
stages N
stairs N
star N
stars N
state N
states N
station N
stations N
steel N
step N
steps N
stomach N
stone N
stones N
store N
stores N
storm N
story N
stranger N
stream N
streams N
street N
streets N
strength N
structure N
structures N
student N
style N
success N
sugar N
suit N
sukuma N
sun N
sunrise N
sunset N
supporter N
surface N
surfaces N
surgeon N
survivor N
suspect N
swahili N
swamp N
swamps N
swimmer N
swimmers N
switch N
switches N
sword N
swords N
symbol N
symbols N
system N
systems N
table N
tables N
tablet N
tablets N
tea N
teacher N
teachers N
team N
technology N
teen N
teenager N
teeth N
television N
temperature N
temple N
temples N
text N
texts N
therapist N
thesis N
thika N
thing N
things N
thoughts N
throat N
thumb N
thumbs N
thunder N
tide N
tides N
tiger N
tigers N
time N
times N
toad N
toads N
toe N
toes N
tongue N
tool N
tools N
tooth N
tourist N
toy N
toys N
tradition N
trainer N
traveler N
tree N
trees N
truck N
trucks N
truth N
turkana N
turkey N
turkeys N
turtle N
turtles N
tv N
type N
ugali N
uhuru N
uncle N
uniform N
university N
valley N
valleys N
value N
values N
van N
vans N
vegetable N
vegetables N
vein N
veins N
victim N
view N
villain N
visitor N
visitors N
volcano N
volcanoes N
volunteer N
wall N
wallet N
walls N
war N
watch N
water N
waterfall N
waterfalls N
wave N
waves N
weakness N
weapon N
weapons N
weather N
week N
weeks N
weight N
western N
whale N
whales N
width N
wife N
wildlife N
wind N
window N
windows N
wine N
winner N
wire N
wires N
wisdom N
witness N
wolf N
wolves N
woman N
women N
wood N
word N
words N
worker N
workers N
world N
worm N
worms N
wrist N
wrists N
writer N
writers N
wrong N
year N
years N
zebra N
zebras N
zone N

# ── ADJ (adjectives) ──
able ADJ
absent ADJ
academic ADJ
additional ADJ
advanced ADJ
afraid ADJ
alive ADJ
aliver ADJ
alivest ADJ
amazing ADJ
analytical ADJ
ancient ADJ
angrier ADJ
angriest ADJ
angry ADJ
annual ADJ
anxious ADJ
approved ADJ
ashamed ADJ
available ADJ
awful ADJ
bad ADJ
basic ADJ
beige ADJ
best ADJ
better ADJ
big ADJ
bigger ADJ
biggest ADJ
biological ADJ
black ADJ
blue ADJ
blunt ADJ
bony ADJ
bored ADJ
bossy ADJ
bottom ADJ
bounty ADJ
brave ADJ
braver ADJ
bravest ADJ
breezy ADJ
brief ADJ
bright ADJ
broad ADJ
brown ADJ
bully ADJ
bumpy ADJ
burly ADJ
busier ADJ
busiest ADJ
busty ADJ
busy ADJ
calm ADJ
capable ADJ
central ADJ
chemical ADJ
chilly ADJ
circular ADJ
classic ADJ
classy ADJ
clean ADJ
cleanr ADJ
cleanst ADJ
clear ADJ
clever ADJ
closer ADJ
closest ADJ
clumpy ADJ
cold ADJ
colder ADJ
coldest ADJ
collective ADJ
colorful ADJ
colourful ADJ
comfortable ADJ
common ADJ
complete ADJ
complex ADJ
confused ADJ
cool ADJ
cooler ADJ
coolest ADJ
coral ADJ
correct ADJ
costly ADJ
cosy ADJ
countless ADJ
county ADJ
cowardly ADJ
cozy ADJ
crazy ADJ
cream ADJ
creamy ADJ
creative ADJ
crimson ADJ
crinkly ADJ
critical ADJ
crude ADJ
cruder ADJ
crudest ADJ
cruel ADJ
crusty ADJ
cultural ADJ
curious ADJ
curly ADJ
current ADJ
curved ADJ
cyan ADJ
dainty ADJ
dark ADJ
dead ADJ
deep ADJ
deeper ADJ
deepest ADJ
detailed ADJ
diagonal ADJ
dicey ADJ
digital ADJ
dirtier ADJ
dirtiest ADJ
dirty ADJ
dishonest ADJ
distant ADJ
double ADJ
dreamy ADJ
drier ADJ
driest ADJ
dry ADJ
dusty ADJ
earthy ADJ
easier ADJ
easiest ADJ
easy ADJ
economic ADJ
educational ADJ
electrical ADJ
electronic ADJ
empirical ADJ
empty ADJ
enormous ADJ
environmental ADJ
essential ADJ
ethical ADJ
eventual ADJ
excellent ADJ
excited ADJ
experimental ADJ
extra ADJ
familiar ADJ
fancy ADJ
fantastic ADJ
fat ADJ
fatter ADJ
fattest ADJ
filthy ADJ
final ADJ
fine ADJ
finer ADJ
finest ADJ
fixed ADJ
flat ADJ
flighty ADJ
flimsy ADJ
fluffy ADJ
foamy ADJ
foreign ADJ
formal ADJ
freckly ADJ
frequent ADJ
fresh ADJ
friendly ADJ
front ADJ
frosty ADJ
full ADJ
fundamental ADJ
funnier ADJ
funniest ADJ
funny ADJ
fussy ADJ
future ADJ
general ADJ
generous ADJ
genetic ADJ
gentle ADJ
ghostly ADJ
giant ADJ
glad ADJ
gladder ADJ
gladdest ADJ
global ADJ
gloomy ADJ
gnarly ADJ
golden ADJ
good ADJ
gradual ADJ
grateful ADJ
gray ADJ
greasy ADJ
great ADJ
greater ADJ
greatest ADJ
greedy ADJ
green ADJ
grey ADJ
grizzly ADJ
grumpy ADJ
guilty ADJ
gusty ADJ
happier ADJ
happiest ADJ
happy ADJ
harder ADJ
hardest ADJ
hazy ADJ
healthier ADJ
healthiest ADJ
healthy ADJ
heavier ADJ
heaviest ADJ
heavy ADJ
high ADJ
higher ADJ
highest ADJ
hilly ADJ
historical ADJ
hollow ADJ
holy ADJ
honest ADJ
horizontal ADJ
horny ADJ
hot ADJ
hotter ADJ
hottest ADJ
huge ADJ
huger ADJ
hugest ADJ
hungrier ADJ
hungriest ADJ
hungry ADJ
icy ADJ
ighty ADJ
ill ADJ
immediate ADJ
impatient ADJ
incorrect ADJ
incredible ADJ
indigo ADJ
individual ADJ
indoor ADJ
infinite ADJ
informal ADJ
inner ADJ
instant ADJ
intelligent ADJ
international ADJ
invalid ADJ
ivory ADJ
jealous ADJ
jolly ADJ
juicy ADJ
kind ADJ
large ADJ
larger ADJ
largest ADJ
lazy ADJ
legal ADJ
lengthy ADJ
light ADJ
limited ADJ
linguistic ADJ
literary ADJ
littler ADJ
littlest ADJ
lively ADJ
local ADJ
lonely ADJ
long ADJ
longer ADJ
longest ADJ
lovely ADJ
low ADJ
lower ADJ
lowest ADJ
loyal ADJ
luckier ADJ
luckiest ADJ
lucky ADJ
lumpy ADJ
mad ADJ
madder ADJ
maddest ADJ
magenta ADJ
main ADJ
major ADJ
maroon ADJ
massive ADJ
mathematical ADJ
mechanical ADJ
medical ADJ
melted ADJ
messier ADJ
messiest ADJ
messy ADJ
microscopic ADJ
mighty ADJ
mini ADJ
minor ADJ
missing ADJ
misty ADJ
modern ADJ
moment ADJ
mossy ADJ
mousey ADJ
multiple ADJ
musty ADJ
narrow ADJ
narrower ADJ
narrowest ADJ
national ADJ
navy ADJ
nervous ADJ
new ADJ
nice ADJ
nicer ADJ
nicest ADJ
nighty ADJ
noble ADJ
noisier ADJ
noisiest ADJ
noisy ADJ
normal ADJ
nuclear ADJ
numerous ADJ
occasional ADJ
odd ADJ
official ADJ
old ADJ
optional ADJ
orange ADJ
ordinary ADJ
original ADJ
outdoor ADJ
outer ADJ
pale ADJ
parallel ADJ
partial ADJ
patient ADJ
perfect ADJ
permanent ADJ
personal ADJ
philosophical ADJ
phony ADJ
physical ADJ
pink ADJ
plenty ADJ
pointy ADJ
polite ADJ
politer ADJ
politest ADJ
political ADJ
poor ADJ
poorer ADJ
poorest ADJ
posy ADJ
practical ADJ
present ADJ
previous ADJ
pricey ADJ
prickly ADJ
primary ADJ
private ADJ
professional ADJ
proud ADJ
public ADJ
puffy ADJ
pure ADJ
purer ADJ
purest ADJ
purple ADJ
quick ADJ
rainbow ADJ
rapid ADJ
rare ADJ
raw ADJ
recent ADJ
rectangular ADJ
red ADJ
regular ADJ
rejected ADJ
relaxed ADJ
religious ADJ
remote ADJ
rich ADJ
richer ADJ
richest ADJ
ripe ADJ
riper ADJ
ripest ADJ
roomy ADJ
rosy ADJ
round ADJ
rude ADJ
ruder ADJ
rudest ADJ
rural ADJ
rusty ADJ
sad ADJ
sadder ADJ
saddest ADJ
safe ADJ
safer ADJ
safest ADJ
salmon ADJ
sassy ADJ
scanty ADJ
scarier ADJ
scariest ADJ
scarlet ADJ
scary ADJ
scientific ADJ
secondary ADJ
selfish ADJ
serious ADJ
shallow ADJ
shallower ADJ
shallowest ADJ
sharp ADJ
shiny ADJ
short ADJ
shorter ADJ
shortest ADJ
sick ADJ
silly ADJ
silver ADJ
simple ADJ
single ADJ
skinny ADJ
slim ADJ
slimmer ADJ
slimmest ADJ
small ADJ
smaller ADJ
smallest ADJ
smart ADJ
social ADJ
soft ADJ
softer ADJ
softest ADJ
solid ADJ
spare ADJ
sparkly ADJ
special ADJ
specific ADJ
spicy ADJ
square ADJ
stable ADJ
stale ADJ
stealthy ADJ
steamy ADJ
stony ADJ
stormy ADJ
straight ADJ
strange ADJ
stressed ADJ
stuffy ADJ
sudden ADJ
suitable ADJ
surly ADJ
surprised ADJ
swift ADJ
tall ADJ
taller ADJ
tallest ADJ
tastier ADJ
tastiest ADJ
tasty ADJ
teal ADJ
technical ADJ
temporary ADJ
terrible ADJ
theoretical ADJ
thick ADJ
thicker ADJ
thickest ADJ
thin ADJ
thinner ADJ
thinnest ADJ
thorny ADJ
tighty ADJ
tiny ADJ
tired ADJ
toasty ADJ
top ADJ
total ADJ
tough ADJ
tougher ADJ
toughest ADJ
traditional ADJ
transparent ADJ
triangular ADJ
trickier ADJ
trickiest ADJ
tricky ADJ
turquoise ADJ
typical ADJ
uglier ADJ
ugliest ADJ
ugly ADJ
underground ADJ
unique ADJ
universal ADJ
unusual ADJ
urban ADJ
valid ADJ
various ADJ
vast ADJ
vertical ADJ
violent ADJ
violet ADJ
warm ADJ
warmer ADJ
warmest ADJ
wavy ADJ
wealthy ADJ
weird ADJ
wet ADJ
wetter ADJ
wettest ADJ
white ADJ
whole ADJ
wide ADJ
wider ADJ
widest ADJ
wise ADJ
wiser ADJ
wisest ADJ
wonderful ADJ
woolly ADJ
wormy ADJ
worried ADJ
worse ADJ
worst ADJ
worthy ADJ
wrinkly ADJ
yellow ADJ
young ADJ

# ── ADV (adverbs) ──
abroad ADV
academically ADV
actually ADV
again ADV
ago ADV
ahead ADV
almost ADV
already ADV
always ADV
annually ADV
approximately ADV
artificially ADV
automatically ADV
away ADV
back ADV
badly ADV
barely ADV
broadly ADV
carefully ADV
carelessly ADV
closely ADV
completely ADV
constantly ADV
continuously ADV
creatively ADV
culturally ADV
currently ADV
daily ADV
deeply ADV
directly ADV
downstairs ADV
early ADV
easily ADV
east ADV
effectively ADV
emotionally ADV
entirely ADV
especially ADV
essentially ADV
extremely ADV
fairly ADV
far ADV
fast ADV
financially ADV
firmly ADV
first ADV
formally ADV
formerly ADV
fortunately ADV
forward ADV
frequently ADV
fully ADV
generally ADV
gently ADV
globally ADV
gradually ADV
hard ADV
hardly ADV
heavily ADV
highly ADV
ideally ADV
immediately ADV
importantly ADV
incredibly ADV
independently ADV
indirectly ADV
informally ADV
instantly ADV
interestingly ADV
inward ADV
ironically ADV
largely ADV
late ADV
lately ADV
legally ADV
lightly ADV
locally ADV
loosely ADV
loudly ADV
luckily ADV
mainly ADV
manually ADV
mentally ADV
monthly ADV
mostly ADV
nationwide ADV
naturally ADV
nearly ADV
never ADV
next ADV
normally ADV
north ADV
occasionally ADV
officially ADV
often ADV
only ADV
openly ADV
outward ADV
particularly ADV
partly ADV
personally ADV
physically ADV
politically ADV
practically ADV
precisely ADV
presently ADV
previously ADV
professionally ADV
publicly ADV
purely ADV
quickly ADV
quietly ADV
quite ADV
rapidly ADV
rarely ADV
rather ADV
recently ADV
regularly ADV
repeatedly ADV
roughly ADV
scientifically ADV
secretly ADV
seldom ADV
sharply ADV
sideways ADV
significantly ADV
slow ADV
slowly ADV
smoothly ADV
socially ADV
softly ADV
sometimes ADV
soon ADV
south ADV
still ADV
strongly ADV
suddenly ADV
surprisingly ADV
technically ADV
then ADV
theoretically ADV
tightly ADV
today ADV
together ADV
tomorrow ADV
tonight ADV
too ADV
totally ADV
truly ADV
typically ADV
upstairs ADV
usually ADV
very ADV
weakly ADV
weekly ADV
west ADV
widely ADV
worldwide ADV
yearly ADV
yesterday ADV

# ── CUSTOM FIXES ──
for PREP
tomorrow N
rain V

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
            continue;
        } else if (!at_end()) {
            shift();
        } else {
            // Stuck: Cannot shift and cannot reduce, but not in accept state
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
    // Shift-reduce parsing priority for proper nested reductions:
    if (reduce_PP()) return true;
    if (reduce_NP()) return true;
    // VERY IMPORTANT FIX: If the next token could shift into a valid longer match,
    // we should NOT eagerly reduce VP or S.
    // However, our grammar is simple enough that we just attempt reduce in priority order.
    // To handle prepositions, shift-reduce parsers typically resolve shift/reduce conflicts 
    // by looking ahead. Let's do a simple 1-token lookahead to avoid reducing VP too early
    // when a PP could be formed.
    
    if (stack_top_matches({"V", "NP"}) || stack_top_matches({"V"}) || stack_top_matches({"AUX", "V"}) || stack_top_matches({"AUX", "NP"})) {
        if (!at_end() && (pos_to_str(tokens_[input_pos_].tag) == "PREP" || 
                          pos_to_str(tokens_[input_pos_].tag) == "PRON" ||
                          pos_to_str(tokens_[input_pos_].tag) == "DET" ||
                          pos_to_str(tokens_[input_pos_].tag) == "ADJ" ||
                          pos_to_str(tokens_[input_pos_].tag) == "PROPER_N" ||
                          pos_to_str(tokens_[input_pos_].tag) == "N" ||
                          pos_to_str(tokens_[input_pos_].tag) == "ADV" ||
                          pos_to_str(tokens_[input_pos_].tag) == "V" ||
                          pos_to_str(tokens_[input_pos_].tag) == "AUX")) {
            return false; // Shift to allow a longer VP rule to trigger (like V NP or V NP PP or V ADV) or S rule
        }
    }

    if (stack_top_matches({"INTJ"}) || stack_top_matches({"INTJ", "NP"})) {
        if (!at_end()) {
            return false; // Shift to allow INTJ S or INTJ NP ADV
        }
    }
    
    if (reduce_VP()) return true;
    if (reduce_S()) return true;
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
    if (stack_top_matches({"DET", "N"})) {
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
    if (stack_top_matches({"PRON"})) {
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

    if (stack_top_matches({"N", "N"})) {
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
    if (stack_top_matches({"N"})) {
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
    if (stack_top_matches({"V"})) {
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
    if (stack_top_matches({"VP"})) {
        auto node = std::make_unique<ParseNode>();
        node->label = "S";
        node->type = NodeType::NON_TERMINAL;
        auto vp = std::move(stack_.back().node); stack_.pop_back();
        node->add_child(std::move(vp));
        stack_.push_back({std::move(node), "S"});
        return true;
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
            continue; // Skip apostrophe to support contractions like "doesn't" -> "doesnt"
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
            if (token.tag == POS::NUM || token.tag == POS::OP) {
                is_expr = true;
                break;
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
        
        if (parent_label == "NP") {
            if (node->label == "DET") role = "NP.determiner";
            else if (node->label == "N" || node->label == "PRON" || node->label == "PROPER_N") role = "NP.head";
            else if (node->label == "ADJ") role = "NP.modifier";
            else role = parent_label + "." + node->label;
        } else if (parent_label == "VP") {
            if (node->label == "V") role = "VP.head";
            else if (node->label == "AUX") role = "VP.auxiliary";
            else if (node->label == "ADV" || node->label == "ADJ") role = "VP.modifier";
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
        } else {
            role = parent_label + "." + node->label;
        }

        entries_.push_back({counter_++, node->lexeme, node->label, role, scope});
    } else {
        std::string next_scope = scope;
        if (node->label == "PP") {
            next_scope = "Prepositional";
        }
        
        for (const auto& child : node->children) {
            traverse(child.get(), node->label, next_scope);
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

TopDownParser::TopDownParser(const std::vector<Token>& tokens) 
    : tokens_(tokens), cursor_(0) {}

std::unique_ptr<ParseNode> TopDownParser::parse() {
    cursor_ = 0;

    bool is_expr = false;
    for (const auto& token : tokens_) {
        if (token.tag == POS::NUM || token.tag == POS::OP) {
            is_expr = true;
            break;
        }
    }

    std::unique_ptr<ParseNode> root;
    if (is_expr) {
        root = parse_EXPR();
    } else {
        root = parse_S();
    }
    
    // To be a fully valid parse, we must have consumed all tokens.
    if (root && at_end()) {
        return root;
    }
    
    return nullptr;
}

const Token& TopDownParser::current() const {
    if (at_end()) {
        // Return a dummy token representing EOF safely
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
    if (current().tag == expected) {
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
    size_t saved_cursor = cursor_;
    
    // S -> CONJ S S (Handles: "Although you were late you did your homework")
    auto s_conj_s_s = std::make_unique<ParseNode>();
    s_conj_s_s->label = "S";
    s_conj_s_s->type = NodeType::NON_TERMINAL;
    if (consume(POS::CONJ, s_conj_s_s.get())) {
        if (auto s1_child = parse_S()) {
            s_conj_s_s->add_child(std::move(s1_child));
            if (auto s2_child = parse_S()) {
                s_conj_s_s->add_child(std::move(s2_child));
                
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s_conj_s_s));
            new_s->add_child(std::move(pp));
            s_conj_s_s = std::move(new_s);
        }
        return s_conj_s_s;

            }
        }
    }
    cursor_ = saved_cursor;

    // S -> NP VP AUX NP (Handles Tag Questions: "you will be available, won't you")
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
                    
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s_tag_question));
            new_s->add_child(std::move(pp));
            s_tag_question = std::move(new_s);
        }
        return s_tag_question;

                }
            }
        }
    }
    cursor_ = saved_cursor;

    // S -> NP VP CONJ NP (Handles: "we will come, however the circumstance")
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
                    
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s_np_vp_conj_np));
            new_s->add_child(std::move(pp));
            s_np_vp_conj_np = std::move(new_s);
        }
        return s_np_vp_conj_np;

                }
            }
        }
    }
    cursor_ = saved_cursor;

    // S -> NP AUX NP VP
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
                    
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s_np_aux));
            new_s->add_child(std::move(pp));
            s_np_aux = std::move(new_s);
        }
        return s_np_aux;

                }
            }
        }
    }
    cursor_ = saved_cursor;

    // S -> NP VP PP
    auto s1 = std::make_unique<ParseNode>();
    s1->label = "S";
    s1->type = NodeType::NON_TERMINAL;
    if (auto np = parse_NP()) {
        s1->add_child(std::move(np));
        if (auto vp = parse_VP()) {
            s1->add_child(std::move(vp));
            if (auto pp = parse_PP()) {
                s1->add_child(std::move(pp));
                
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s1));
            new_s->add_child(std::move(pp));
            s1 = std::move(new_s);
        }
        return s1;

            }
        }
    }
    cursor_ = saved_cursor;

    // S -> NP VP
    auto s2 = std::make_unique<ParseNode>();
    s2->label = "S";
    s2->type = NodeType::NON_TERMINAL;
    if (auto np = parse_NP()) {
        s2->add_child(std::move(np));
        if (auto vp = parse_VP()) {
            s2->add_child(std::move(vp));
            
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s2));
            new_s->add_child(std::move(pp));
            s2 = std::move(new_s);
        }
        return s2;

        }
    }
    cursor_ = saved_cursor;

    // S -> AUX NP VP
    auto s_aux = std::make_unique<ParseNode>();
    s_aux->label = "S";
    s_aux->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, s_aux.get())) {
        if (auto np = parse_NP()) {
            s_aux->add_child(std::move(np));
            if (auto vp = parse_VP()) {
                s_aux->add_child(std::move(vp));
                
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s_aux));
            new_s->add_child(std::move(pp));
            s_aux = std::move(new_s);
        }
        return s_aux;

            }
        }
    }
    cursor_ = saved_cursor;

    // S -> VP
    auto s_vp = std::make_unique<ParseNode>();
    s_vp->label = "S";
    s_vp->type = NodeType::NON_TERMINAL;
    if (auto vp = parse_VP()) {
        s_vp->add_child(std::move(vp));
        
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s_vp));
            new_s->add_child(std::move(pp));
            s_vp = std::move(new_s);
        }
        return s_vp;

    }
    cursor_ = saved_cursor;

    // S -> INTJ S
    auto s_intj_s = std::make_unique<ParseNode>();
    s_intj_s->label = "S";
    s_intj_s->type = NodeType::NON_TERMINAL;
    if (consume(POS::INTJ, s_intj_s.get())) {
        if (auto s = parse_S()) {
            s_intj_s->add_child(std::move(s));
            
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s_intj_s));
            new_s->add_child(std::move(pp));
            s_intj_s = std::move(new_s);
        }
        return s_intj_s;

        }
    }
    cursor_ = saved_cursor;

    // S -> INTJ NP ADV
    auto s_intj_np_adv = std::make_unique<ParseNode>();
    s_intj_np_adv->label = "S";
    s_intj_np_adv->type = NodeType::NON_TERMINAL;
    if (consume(POS::INTJ, s_intj_np_adv.get())) {
        if (auto np = parse_NP()) {
            s_intj_np_adv->add_child(std::move(np));
            if (consume(POS::ADV, s_intj_np_adv.get())) {
                
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s_intj_np_adv));
            new_s->add_child(std::move(pp));
            s_intj_np_adv = std::move(new_s);
        }
        return s_intj_np_adv;

            }
        }
    }
    cursor_ = saved_cursor;

    // S -> INTJ NP
    auto s3 = std::make_unique<ParseNode>();
    s3->label = "S";
    s3->type = NodeType::NON_TERMINAL;
    if (consume(POS::INTJ, s3.get())) {
        if (auto np = parse_NP()) {
            s3->add_child(std::move(np));
            
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s3));
            new_s->add_child(std::move(pp));
            s3 = std::move(new_s);
        }
        return s3;

        }
    }
    cursor_ = saved_cursor;

    // S -> INTJ
    auto s4 = std::make_unique<ParseNode>();
    s4->label = "S";
    s4->type = NodeType::NON_TERMINAL;
    if (consume(POS::INTJ, s4.get())) {
        
        while (auto pp = parse_PP()) {
            auto new_s = std::make_unique<ParseNode>();
            new_s->label = "S";
            new_s->type = NodeType::NON_TERMINAL;
            new_s->add_child(std::move(s4));
            new_s->add_child(std::move(pp));
            s4 = std::move(new_s);
        }
        return s4;

    }
    cursor_ = saved_cursor;
    
    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_NP() {
    size_t saved_cursor = cursor_;

    // NP -> DET ADJ N
    auto np_dan = std::make_unique<ParseNode>();
    np_dan->label = "NP";
    np_dan->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np_dan.get()) && consume(POS::ADJ, np_dan.get()) && consume(POS::N, np_dan.get())) {
        return np_dan;
    }
    cursor_ = saved_cursor;


    
    // NP -> DET ADJ ADJ N
    auto np1 = std::make_unique<ParseNode>();
    np1->label = "NP";
    np1->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np1.get()) &&
        consume(POS::ADJ, np1.get()) &&
        consume(POS::ADJ, np1.get()) &&
        consume(POS::N, np1.get())) {
        return np1;
    }
    cursor_ = saved_cursor;

    // NP -> DET ADJ N
    auto np2 = std::make_unique<ParseNode>();
    np2->label = "NP";
    np2->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np2.get()) &&
        consume(POS::ADJ, np2.get()) &&
        consume(POS::N, np2.get())) {
        return np2;
    }
    cursor_ = saved_cursor;


    // NP -> DET N N
    auto np_dnn = std::make_unique<ParseNode>();
    np_dnn->label = "NP";
    np_dnn->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np_dnn.get()) &&
        consume(POS::N, np_dnn.get()) &&
        consume(POS::N, np_dnn.get())) {
        return np_dnn;
    }
    cursor_ = saved_cursor;

    // NP -> N N
    auto np_nn = std::make_unique<ParseNode>();
    np_nn->label = "NP";
    np_nn->type = NodeType::NON_TERMINAL;
    if (consume(POS::N, np_nn.get()) &&
        consume(POS::N, np_nn.get())) {
        return np_nn;
    }
    cursor_ = saved_cursor;

    // NP -> DET N
    auto np3 = std::make_unique<ParseNode>();
    np3->label = "NP";
    np3->type = NodeType::NON_TERMINAL;
    if (consume(POS::DET, np3.get()) &&
        consume(POS::N, np3.get())) {
        return np3;
    }
    cursor_ = saved_cursor;

    // NP -> PRON
    auto np4 = std::make_unique<ParseNode>();
    np4->label = "NP";
    np4->type = NodeType::NON_TERMINAL;
    if (consume(POS::PRON, np4.get())) {
        return np4;
    }
    cursor_ = saved_cursor;

    // NP -> PROPER_N
    auto np5 = std::make_unique<ParseNode>();
    np5->label = "NP";
    np5->type = NodeType::NON_TERMINAL;
    if (consume(POS::PROPER_N, np5.get())) {
        return np5;
    }
    cursor_ = saved_cursor;

    // NP -> N
    auto np6 = std::make_unique<ParseNode>();
    np6->label = "NP";
    np6->type = NodeType::NON_TERMINAL;
    if (consume(POS::N, np6.get())) {
        return np6;
    }
    cursor_ = saved_cursor;

    return nullptr;
}

std::unique_ptr<ParseNode> TopDownParser::parse_VP() {
    size_t saved_cursor = cursor_;

    // VP -> AUX V NP ADV
    auto vp_aux_v_np_adv = std::make_unique<ParseNode>();
    vp_aux_v_np_adv->label = "VP";
    vp_aux_v_np_adv->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_v_np_adv.get()) && consume(POS::V, vp_aux_v_np_adv.get())) {
        if (auto np = parse_NP()) {
            vp_aux_v_np_adv->add_child(std::move(np));
            if (consume(POS::ADV, vp_aux_v_np_adv.get())) {
                
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux_v_np_adv));
            new_vp->add_child(std::move(pp));
            vp_aux_v_np_adv = std::move(new_vp);
        }
        return vp_aux_v_np_adv;

            }
        }
    }
    cursor_ = saved_cursor;

    // VP -> AUX V NP PP
    auto vp_aux1 = std::make_unique<ParseNode>();
    vp_aux1->label = "VP";
    vp_aux1->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux1.get()) && consume(POS::V, vp_aux1.get())) {
        if (auto np = parse_NP()) {
            vp_aux1->add_child(std::move(np));
            if (auto pp = parse_PP()) {
                vp_aux1->add_child(std::move(pp));
                
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux1));
            new_vp->add_child(std::move(pp));
            vp_aux1 = std::move(new_vp);
        }
        return vp_aux1;

            }
        }
    }
    cursor_ = saved_cursor;

    // VP -> AUX V NP
    auto vp_aux2 = std::make_unique<ParseNode>();
    vp_aux2->label = "VP";
    vp_aux2->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux2.get()) && consume(POS::V, vp_aux2.get())) {
        if (auto np = parse_NP()) {
            vp_aux2->add_child(std::move(np));
            
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux2));
            new_vp->add_child(std::move(pp));
            vp_aux2 = std::move(new_vp);
        }
        return vp_aux2;

        }
    }
    cursor_ = saved_cursor;

    // VP -> AUX V PP
    auto vp_aux_v_pp = std::make_unique<ParseNode>();
    vp_aux_v_pp->label = "VP";
    vp_aux_v_pp->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_v_pp.get()) && consume(POS::V, vp_aux_v_pp.get())) {
        if (auto pp = parse_PP()) {
            vp_aux_v_pp->add_child(std::move(pp));
            
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux_v_pp));
            new_vp->add_child(std::move(pp));
            vp_aux_v_pp = std::move(new_vp);
        }
        return vp_aux_v_pp;

        }
    }
    cursor_ = saved_cursor;

    // VP -> AUX V ADV
    auto vp_aux_v_adv = std::make_unique<ParseNode>();
    vp_aux_v_adv->label = "VP";
    vp_aux_v_adv->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_v_adv.get()) && consume(POS::V, vp_aux_v_adv.get()) && consume(POS::ADV, vp_aux_v_adv.get())) {
        
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux_v_adv));
            new_vp->add_child(std::move(pp));
            vp_aux_v_adv = std::move(new_vp);
        }
        return vp_aux_v_adv;

    }
    cursor_ = saved_cursor;

    // VP -> AUX ADV V
    auto vp_aux_adv_v = std::make_unique<ParseNode>();
    vp_aux_adv_v->label = "VP";
    vp_aux_adv_v->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_adv_v.get()) && consume(POS::ADV, vp_aux_adv_v.get()) && consume(POS::V, vp_aux_adv_v.get())) {
        
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux_adv_v));
            new_vp->add_child(std::move(pp));
            vp_aux_adv_v = std::move(new_vp);
        }
        return vp_aux_adv_v;

    }
    cursor_ = saved_cursor;

    // VP -> AUX V
    auto vp_aux3 = std::make_unique<ParseNode>();
    vp_aux3->label = "VP";
    vp_aux3->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux3.get()) && consume(POS::V, vp_aux3.get())) {
        
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux3));
            new_vp->add_child(std::move(pp));
            vp_aux3 = std::move(new_vp);
        }
        return vp_aux3;

    }
    cursor_ = saved_cursor;

    // VP -> AUX ADV
    auto vp_aux_adv = std::make_unique<ParseNode>();
    vp_aux_adv->label = "VP";
    vp_aux_adv->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_adv.get()) && consume(POS::ADV, vp_aux_adv.get())) {
        
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux_adv));
            new_vp->add_child(std::move(pp));
            vp_aux_adv = std::move(new_vp);
        }
        return vp_aux_adv;

    }
    cursor_ = saved_cursor;

    // VP -> AUX NP PP
    auto vp_aux_np_pp = std::make_unique<ParseNode>();
    vp_aux_np_pp->label = "VP";
    vp_aux_np_pp->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_np_pp.get())) {
        if (auto np = parse_NP()) {
            vp_aux_np_pp->add_child(std::move(np));
            if (auto pp = parse_PP()) {
                vp_aux_np_pp->add_child(std::move(pp));
                
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux_np_pp));
            new_vp->add_child(std::move(pp));
            vp_aux_np_pp = std::move(new_vp);
        }
        return vp_aux_np_pp;

            }
        }
    }
    cursor_ = saved_cursor;

    // VP -> AUX NP ADV
    auto vp_aux_np_adv = std::make_unique<ParseNode>();
    vp_aux_np_adv->label = "VP";
    vp_aux_np_adv->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_np_adv.get())) {
        if (auto np = parse_NP()) {
            vp_aux_np_adv->add_child(std::move(np));
            if (consume(POS::ADV, vp_aux_np_adv.get())) {
                
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux_np_adv));
            new_vp->add_child(std::move(pp));
            vp_aux_np_adv = std::move(new_vp);
        }
        return vp_aux_np_adv;

            }
        }
    }
    cursor_ = saved_cursor;

    // VP -> AUX NP
    auto vp_aux_np = std::make_unique<ParseNode>();
    vp_aux_np->label = "VP";
    vp_aux_np->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_np.get())) {
        if (auto np = parse_NP()) {
            vp_aux_np->add_child(std::move(np));
            
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux_np));
            new_vp->add_child(std::move(pp));
            vp_aux_np = std::move(new_vp);
        }
        return vp_aux_np;

        }
    }
    cursor_ = saved_cursor;

    // VP -> AUX ADJ
    auto vp_aux_adj = std::make_unique<ParseNode>();
    vp_aux_adj->label = "VP";
    vp_aux_adj->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_adj.get()) && consume(POS::ADJ, vp_aux_adj.get())) {
        
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux_adj));
            new_vp->add_child(std::move(pp));
            vp_aux_adj = std::move(new_vp);
        }
        return vp_aux_adj;

    }
    cursor_ = saved_cursor;

    // VP -> AUX VP (Recursive Stacking)
    auto vp_aux_vp = std::make_unique<ParseNode>();
    vp_aux_vp->label = "VP";
    vp_aux_vp->type = NodeType::NON_TERMINAL;
    if (consume(POS::AUX, vp_aux_vp.get())) {
        if (auto vp_child = parse_VP()) {
            vp_aux_vp->add_child(std::move(vp_child));
            
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_aux_vp));
            new_vp->add_child(std::move(pp));
            vp_aux_vp = std::move(new_vp);
        }
        return vp_aux_vp;

        }
    }
    cursor_ = saved_cursor;

    // VP -> V NP PP
    auto vp1 = std::make_unique<ParseNode>();
    vp1->label = "VP";
    vp1->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp1.get())) {
        if (auto np = parse_NP()) {
            vp1->add_child(std::move(np));
            if (auto pp = parse_PP()) {
                vp1->add_child(std::move(pp));
                
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp1));
            new_vp->add_child(std::move(pp));
            vp1 = std::move(new_vp);
        }
        return vp1;

            }
        }
    }
    cursor_ = saved_cursor;

    // VP -> V NP ADV
    auto vp_v_np_adv = std::make_unique<ParseNode>();
    vp_v_np_adv->label = "VP";
    vp_v_np_adv->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp_v_np_adv.get())) {
        if (auto np = parse_NP()) {
            vp_v_np_adv->add_child(std::move(np));
            if (consume(POS::ADV, vp_v_np_adv.get())) {
                
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp_v_np_adv));
            new_vp->add_child(std::move(pp));
            vp_v_np_adv = std::move(new_vp);
        }
        return vp_v_np_adv;

            }
        }
    }
    cursor_ = saved_cursor;

    // VP -> V NP
    auto vp2 = std::make_unique<ParseNode>();
    vp2->label = "VP";
    vp2->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp2.get())) {
        if (auto np = parse_NP()) {
            vp2->add_child(std::move(np));
            
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp2));
            new_vp->add_child(std::move(pp));
            vp2 = std::move(new_vp);
        }
        return vp2;

        }
    }
    cursor_ = saved_cursor;

    // VP -> V PP
    auto vp3 = std::make_unique<ParseNode>();
    vp3->label = "VP";
    vp3->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp3.get())) {
        if (auto pp = parse_PP()) {
            vp3->add_child(std::move(pp));
            
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp3));
            new_vp->add_child(std::move(pp));
            vp3 = std::move(new_vp);
        }
        return vp3;

        }
    }
    cursor_ = saved_cursor;

    // VP -> V ADV
    auto vp4 = std::make_unique<ParseNode>();
    vp4->label = "VP";
    vp4->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp4.get()) && consume(POS::ADV, vp4.get())) {
        
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp4));
            new_vp->add_child(std::move(pp));
            vp4 = std::move(new_vp);
        }
        return vp4;

    }
    cursor_ = saved_cursor;

    // VP -> V
    auto vp5 = std::make_unique<ParseNode>();
    vp5->label = "VP";
    vp5->type = NodeType::NON_TERMINAL;
    if (consume(POS::V, vp5.get())) {
        
        while (auto pp = parse_PP()) {
            auto new_vp = std::make_unique<ParseNode>();
            new_vp->label = "VP";
            new_vp->type = NodeType::NON_TERMINAL;
            new_vp->add_child(std::move(vp5));
            new_vp->add_child(std::move(pp));
            vp5 = std::move(new_vp);
        }
        return vp5;

    }
    cursor_ = saved_cursor;

    return nullptr;
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

## File: `tests/fixtures/sentences.txt`

```text
The dog sees a cat
The quick brown fox jumps over the lazy dog
A man is holding a book
The tall child walks to the house
She gives a good book
The cat runs quickly
3 + 4 * 2
(5 + 2) * 8
10 - 2 + 5 * (3 + 4)
7 * 8 + 9 / 3

```

## File: `tests/test_bottom_up.cpp`

```cpp
#include <gtest/gtest.h>
#include "lexer.h"
#include "bottom_up_parser.h"

std::unique_ptr<ParseNode> parse_bu(const std::string& input) {
    Lexer lexer(input);
    auto tokens = lexer.tokenize();
    BottomUpParser parser(tokens);
    return parser.parse();
}

TEST(BottomUpTest, SimpleSentence) {
    auto tree = parse_bu("The cat runs");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[1]->label, "VP");
}

TEST(BottomUpTest, ComplexSentence) {
    auto tree = parse_bu("The quick brown fox jumps over the lazy dog");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[1]->label, "VP");
    EXPECT_EQ(tree->children[1]->children.size(), 2);
    EXPECT_EQ(tree->children[1]->children[1]->label, "PP");
}

TEST(BottomUpTest, PronounSentence) {
    auto tree = parse_bu("She loves him");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[0]->children[0]->lexeme, "She");
}

TEST(BottomUpTest, PrepositionalPhrase) {
    auto tree = parse_bu("The dog sleeps in the house");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children.size(), 2);
    EXPECT_EQ(tree->children[1]->children.size(), 2); // V and PP
    EXPECT_EQ(tree->children[1]->children[1]->label, "PP");
}

TEST(BottomUpTest, BareNounVerb) {
    auto tree = parse_bu("fox jumps");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
}

TEST(BottomUpTest, FailsOnNonsense) {
    auto tree = parse_bu("jumps the the");
    EXPECT_EQ(tree, nullptr);
}

TEST(BottomUpTest, IncompleteSentence) {
    auto tree = parse_bu("The dog");
    EXPECT_EQ(tree, nullptr);
}

TEST(BottomUpTest, AuxiliaryVerb) {
    auto tree = parse_bu("The dog is running");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->children[1]->label, "VP");
    EXPECT_EQ(tree->children[1]->children[0]->label, "AUX");
}

```

## File: `tests/test_display.cpp`

```cpp
#include <gtest/gtest.h>
#include "parse_tree.h"
#include "display.h"
#include <sstream>

TEST(DisplayTest, SimpleTreeRendering) {
    auto root = std::make_unique<ParseNode>();
    root->label = "S";
    root->type = NodeType::NON_TERMINAL;

    auto np = std::make_unique<ParseNode>();
    np->label = "NP";
    np->type = NodeType::NON_TERMINAL;

    auto det = std::make_unique<ParseNode>();
    det->label = "DET";
    det->lexeme = "The";
    det->type = NodeType::TERMINAL;

    auto n = std::make_unique<ParseNode>();
    n->label = "N";
    n->lexeme = "dog";
    n->type = NodeType::TERMINAL;

    np->add_child(std::move(det));
    np->add_child(std::move(n));

    auto vp = std::make_unique<ParseNode>();
    vp->label = "VP";
    vp->type = NodeType::NON_TERMINAL;

    auto v = std::make_unique<ParseNode>();
    v->label = "V";
    v->lexeme = "runs";
    v->type = NodeType::TERMINAL;

    vp->add_child(std::move(v));

    root->add_child(std::move(np));
    root->add_child(std::move(vp));

    // Redirect stdout to capture output
    testing::internal::CaptureStdout();
    Display::print_tree(root.get());
    std::string output = testing::internal::GetCapturedStdout();

    std::string expected = 
        "S\n"
        "├── NP\n"
        "│   ├── DET: \"The\"\n"
        "│   └── N: \"dog\"\n"
        "└── VP\n"
        "    └── V: \"runs\"\n";

    EXPECT_EQ(output, expected);
}

```

## File: `tests/test_lexer.cpp`

```cpp
#include <gtest/gtest.h>
#include "lexer.h"

TEST(LexerTest, Determiners) {
    Lexer l("the");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].tag, POS::DET);
}

TEST(LexerTest, PunctuationStripping) {
    Lexer l("Hello, world!");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 2);
    EXPECT_EQ(tokens[0].word, "Hello");
    EXPECT_EQ(tokens[1].word, "world");
}

TEST(LexerTest, SuffixHeuristic_ly) {
    Lexer l("quickly");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].tag, POS::ADV);
}

TEST(LexerTest, SuffixHeuristic_ing) {
    Lexer l("running");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].tag, POS::V);
}

TEST(LexerTest, SuffixHeuristic_ed) {
    Lexer l("walked");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].tag, POS::V);
}

TEST(LexerTest, SuffixHeuristic_tion_ness_ment) {
    Lexer l("action happiness placement");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0].tag, POS::N);
    EXPECT_EQ(tokens[1].tag, POS::N);
    EXPECT_EQ(tokens[2].tag, POS::N);
}

TEST(LexerTest, ProperNounHeuristic) {
    Lexer l("the John runs");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[1].tag, POS::PROPER_N);
}

TEST(LexerTest, BasicSentence) {
    Lexer l("The quick brown fox jumps.");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 5);
    EXPECT_EQ(tokens[0].tag, POS::DET);
    EXPECT_EQ(tokens[1].tag, POS::ADJ);
    EXPECT_EQ(tokens[2].tag, POS::ADJ);
    EXPECT_EQ(tokens[3].tag, POS::N);
    EXPECT_EQ(tokens[4].tag, POS::V);
}

TEST(LexerTest, UnknownWord) {
    Lexer l("jabberwocky");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].tag, POS::UNKNOWN);
}

TEST(LexerTest, CaseInsensitiveLookup) {
    Lexer l("THE DOG RUNS");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0].tag, POS::DET);
    EXPECT_EQ(tokens[1].tag, POS::N);
    EXPECT_EQ(tokens[2].tag, POS::V);
}

```

## File: `tests/test_symbol_table.cpp`

```cpp
#include <gtest/gtest.h>
#include "lexer.h"
#include "top_down_parser.h"
#include "symbol_table.h"
#include <algorithm>

std::unique_ptr<ParseNode> get_tree(const std::string& input) {
    Lexer lexer(input);
    auto tokens = lexer.tokenize();
    TopDownParser parser(tokens);
    return parser.parse();
}

TEST(SymbolTableTest, ExtractsVerb) {
    auto tree = get_tree("The dog runs");
    SymbolTable st;
    st.build(tree.get());
    auto& entries = st.entries();
    
    auto verb_it = std::find_if(entries.begin(), entries.end(),
        [](const auto& e){ return e.pos_tag == "V"; });
    
    EXPECT_NE(verb_it, entries.end());
    EXPECT_EQ(verb_it->lexeme, "runs");
    EXPECT_EQ(verb_it->grammar_role, "VP.head");
    EXPECT_EQ(verb_it->scope, "Sentence");
}

TEST(SymbolTableTest, PrepPhraseScope) {
    auto tree = get_tree("The dog sleeps in the house");
    SymbolTable st;
    st.build(tree.get());
    auto& entries = st.entries();

    auto prep_it = std::find_if(entries.begin(), entries.end(),
        [](const auto& e){ return e.pos_tag == "PREP"; });
    
    EXPECT_NE(prep_it, entries.end());
    EXPECT_EQ(prep_it->grammar_role, "PP.head");
    EXPECT_EQ(prep_it->scope, "Prepositional");
    
    auto noun_it = std::find_if(entries.rbegin(), entries.rend(),
        [](const auto& e){ return e.pos_tag == "N"; });
    
    EXPECT_NE(noun_it, entries.rend());
    EXPECT_EQ(noun_it->lexeme, "house");
    EXPECT_EQ(noun_it->grammar_role, "NP.head");
    EXPECT_EQ(noun_it->scope, "Prepositional");
}

TEST(SymbolTableTest, CheckGrammarRoles) {
    auto tree = get_tree("The quick brown fox jumps");
    SymbolTable st;
    st.build(tree.get());
    auto& entries = st.entries();

    EXPECT_EQ(entries.size(), 5);
    EXPECT_EQ(entries[0].grammar_role, "NP.determiner"); // The
    EXPECT_EQ(entries[1].grammar_role, "NP.modifier");   // quick
    EXPECT_EQ(entries[2].grammar_role, "NP.modifier");   // brown
    EXPECT_EQ(entries[3].grammar_role, "NP.head");       // fox
    EXPECT_EQ(entries[4].grammar_role, "VP.head");       // jumps
}

```

## File: `tests/test_top_down.cpp`

```cpp
#include <gtest/gtest.h>
#include "lexer.h"
#include "top_down_parser.h"

std::unique_ptr<ParseNode> parse(const std::string& input) {
    Lexer lexer(input);
    auto tokens = lexer.tokenize();
    TopDownParser parser(tokens);
    return parser.parse();
}

TEST(TopDownTest, SimpleSentence) {
    auto tree = parse("The cat runs");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[1]->label, "VP");
}

TEST(TopDownTest, ComplexSentence) {
    auto tree = parse("The quick brown fox jumps over the lazy dog");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[1]->label, "VP");
    EXPECT_EQ(tree->children[1]->children.size(), 2);
    EXPECT_EQ(tree->children[1]->children[1]->label, "PP");
}

TEST(TopDownTest, PronounSentence) {
    auto tree = parse("She loves him");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children[0]->label, "NP");
    EXPECT_EQ(tree->children[0]->children[0]->lexeme, "She");
}

TEST(TopDownTest, PrepositionalPhrase) {
    auto tree = parse("The dog sleeps in the house");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
    EXPECT_EQ(tree->children.size(), 2);
    EXPECT_EQ(tree->children[1]->children.size(), 2); // V and PP
    EXPECT_EQ(tree->children[1]->children[1]->label, "PP");
}

TEST(TopDownTest, BareNounVerb) {
    auto tree = parse("fox jumps");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->label, "S");
}

TEST(TopDownTest, FailsOnNonsense) {
    auto tree = parse("jumps the the");
    EXPECT_EQ(tree, nullptr);
}

TEST(TopDownTest, IncompleteSentence) {
    auto tree = parse("The dog");
    EXPECT_EQ(tree, nullptr); // NP but missing VP
}

TEST(TopDownTest, AuxiliaryVerb) {
    auto tree = parse("The dog is running");
    ASSERT_NE(tree, nullptr);
    EXPECT_EQ(tree->children[1]->label, "VP");
    EXPECT_EQ(tree->children[1]->children[0]->label, "AUX");
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
- S -> NP VP | S PP | NP VP PP | INTJ S | INTJ NP ADV | INTJ NP | INTJ | NP AUX NP VP | AUX NP VP | VP | CONJ S S | NP VP CONJ NP | NP VP AUX NP
- NP -> DET ADJ ADJ N | DET N N | N N | DET ADJ N | DET N | PRON | PROPER_N | N
- VP -> AUX V NP ADV | VP PP | AUX V NP PP | AUX V NP | AUX V PP | AUX V ADV | AUX ADV V | AUX V | AUX NP PP | AUX NP ADV | AUX NP | AUX ADJ | AUX VP | V NP PP | V NP ADV | V NP | V PP | V ADV | V | AUX ADV
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

## File: `patch_debug`

```text
--- src/bottom_up_parser.cpp
+++ src/bottom_up_parser.cpp
@@ -19,6 +19,10 @@
     while (loop_counter++ < max_loops) {
+        std::cout << "Stack: ";
+        for (const auto& item : stack_) std::cout << item.symbol << " ";
+        std::cout << " | Next: " << (at_end() ? "EOF" : pos_to_str(tokens_[input_pos_].tag)) << "\n";
         if (stack_.size() == 1 && stack_.back().symbol == "S" && at_end()) {
             return std::move(stack_.back().node);
         }

```

## File: `update_bottom_up.patch`

```diff
--- src/bottom_up_parser.cpp
+++ src/bottom_up_parser.cpp
@@ -279,6 +279,25 @@
         stack_.push_back({std::move(node), "S"});
         return true;
     }
+    if (stack_top_matches({"INTJ", "NP"})) {
+        auto node = std::make_unique<ParseNode>();
+        node->label = "S";
+        node->type = NodeType::NON_TERMINAL;
+        auto np = std::move(stack_.back().node); stack_.pop_back();
+        auto intj = std::move(stack_.back().node); stack_.pop_back();
+        node->add_child(std::move(intj));
+        node->add_child(std::move(np));
+        stack_.push_back({std::move(node), "S"});
+        return true;
+    }
+    if (stack_top_matches({"INTJ"})) {
+        auto node = std::make_unique<ParseNode>();
+        node->label = "S";
+        node->type = NodeType::NON_TERMINAL;
+        auto intj = std::move(stack_.back().node); stack_.pop_back();
+        node->add_child(std::move(intj));
+        stack_.push_back({std::move(node), "S"});
+        return true;
+    }
     return false;
 }

```

## File: `update_top_down.patch`

```diff
--- src/top_down_parser.cpp
+++ src/top_down_parser.cpp
@@ -67,6 +67,23 @@
 std::unique_ptr<ParseNode> TopDownParser::parse_S() {
     size_t saved_cursor = cursor_;
     
+    // S -> NP AUX NP VP
+    auto s_np_aux = std::make_unique<ParseNode>();
+    s_np_aux->label = "S";
+    s_np_aux->type = NodeType::NON_TERMINAL;
+    if (auto np1 = parse_NP()) {
+        s_np_aux->add_child(std::move(np1));
+        if (consume(POS::AUX, s_np_aux.get())) {
+            if (auto np2 = parse_NP()) {
+                s_np_aux->add_child(std::move(np2));
+                if (auto vp = parse_VP()) {
+                    s_np_aux->add_child(std::move(vp));
+                    return s_np_aux;
+                }
+            }
+        }
+    }
+    cursor_ = saved_cursor;
+
     // S -> NP VP PP
     auto s1 = std::make_unique<ParseNode>();
     s1->label = "S";
@@ -95,6 +112,39 @@
     }
     cursor_ = saved_cursor;
 
+    // S -> AUX NP VP
+    auto s_aux = std::make_unique<ParseNode>();
+    s_aux->label = "S";
+    s_aux->type = NodeType::NON_TERMINAL;
+    if (consume(POS::AUX, s_aux.get())) {
+        if (auto np = parse_NP()) {
+            s_aux->add_child(std::move(np));
+            if (auto vp = parse_VP()) {
+                s_aux->add_child(std::move(vp));
+                return s_aux;
+            }
+        }
+    }
+    cursor_ = saved_cursor;
+
+    // S -> VP
+    auto s_vp = std::make_unique<ParseNode>();
+    s_vp->label = "S";
+    s_vp->type = NodeType::NON_TERMINAL;
+    if (auto vp = parse_VP()) {
+        s_vp->add_child(std::move(vp));
+        return s_vp;
+    }
+    cursor_ = saved_cursor;
+
+    // S -> INTJ S
+    auto s_intj_s = std::make_unique<ParseNode>();
+    s_intj_s->label = "S";
+    s_intj_s->type = NodeType::NON_TERMINAL;
+    if (consume(POS::INTJ, s_intj_s.get())) {
+        if (auto s = parse_S()) {
+            s_intj_s->add_child(std::move(s));
+            return s_intj_s;
+        }
+    }
+    cursor_ = saved_cursor;
+
+    // S -> INTJ NP ADV
+    auto s_intj_np_adv = std::make_unique<ParseNode>();
+    s_intj_np_adv->label = "S";
+    s_intj_np_adv->type = NodeType::NON_TERMINAL;
+    if (consume(POS::INTJ, s_intj_np_adv.get())) {
+        if (auto np = parse_NP()) {
+            s_intj_np_adv->add_child(std::move(np));
+            if (consume(POS::ADV, s_intj_np_adv.get())) {
+                return s_intj_np_adv;
+            }
+        }
+    }
+    cursor_ = saved_cursor;
+
     // S -> INTJ NP
     auto s3 = std::make_unique<ParseNode>();
     s3->label = "S";
@@ -210,6 +260,25 @@
     }
     cursor_ = saved_cursor;
 
+    // VP -> AUX NP
+    auto vp_aux_np = std::make_unique<ParseNode>();
+    vp_aux_np->label = "VP";
+    vp_aux_np->type = NodeType::NON_TERMINAL;
+    if (consume(POS::AUX, vp_aux_np.get())) {
+        if (auto np = parse_NP()) {
+            vp_aux_np->add_child(std::move(np));
+            return vp_aux_np;
+        }
+    }
+    cursor_ = saved_cursor;
+
+    // VP -> AUX ADJ
+    auto vp_aux_adj = std::make_unique<ParseNode>();
+    vp_aux_adj->label = "VP";
+    vp_aux_adj->type = NodeType::NON_TERMINAL;
+    if (consume(POS::AUX, vp_aux_adj.get()) && consume(POS::ADJ, vp_aux_adj.get())) {
+        return vp_aux_adj;
+    }
+    cursor_ = saved_cursor;
+
     // VP -> V NP PP
     auto vp1 = std::make_unique<ParseNode>();
     vp1->label = "VP";

```
