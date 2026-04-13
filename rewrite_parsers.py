import re

def update_top_down():
    with open('src/top_down_parser.cpp', 'r') as f:
        content = f.read()

    # It's easier to just use bash edit or write for specific parts.
