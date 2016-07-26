#!/bin/bash

power_levels=(15 14 11 8 5 2)
sfs=(sf12 sf11 sf10 sf9 sf8 sf7)
bws=(125 250 500)
delays=(100 150 200 250)
for pw in ${power_levels[*]}; do
	for sf in ${sfs[*]}; do
		for bw in ${bws[*]}; do
			for del in ${delays[*]}; do
				sudo ./send_packets.cpp_exe "$pw" 868100000 "$sf" 4/5 "$bw" on "$del" "$1"
				sleep 1
			done
		done
	done
done