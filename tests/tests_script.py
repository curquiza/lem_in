import os, sys

print 'Ciao les nazes\n'

maps = sorted(os.listdir('maps/'))
print maps
for m in maps:
    if m.endswith('.txt'):
        print m
