#!/bin/bash

echo "Resetting modem(eth1)"
ifdown eth1

ifup eth1
echo "Reset done"
