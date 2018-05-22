import os

all_files = sorted(os.listdir('maps/'))
maps = [f for f in all_files if f.endswith('.txt')]
print maps
