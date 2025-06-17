# Network Interface Monitor

A simple C program to monitor network traffic (bytes transmitted and received) for a given network interface over a time interval.

## Usage

```bash

gcc main.c -o netflow

./netflow -s <seconds> -i <interface>
```

### Tab Completion (zsh)

``````bash

sudo cp _netflow /usr/share/zsh/vendor-completions/`
``````


