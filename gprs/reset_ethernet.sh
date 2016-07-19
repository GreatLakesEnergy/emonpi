#!/bin/bash

echo "Resetting ethernet"
ifdown eth0

ifup eth0
echo "Reset done"
