#!/usr/bin/env python
import sys, smtplib, time
	
fromaddr = "scaparra.jeffrey@mail.navy.mil"
#fromaddr = "From: scaparra.jeffrey@mail.navy.mil"
toaddrs  = ['scaparra.jeffrey@mail.navy.mil']
#toaddrs  = "To: scaparra.jeffrey@mail.navy.mil"
msg = """From: Captain Slow <Captain.Slow@KernelPanic.ncr.spawar.navy.mil>
To: Developers <Developers@pvat>
Subject: Test


This is an automated message.
"""
#server = smtplib.SMTP('ms1.mail.navy.mil')
try:
	server = smtplib.SMTP('ins.ncr.spawar.navy.mil')
	server.sendmail(fromaddr, toaddrs, msg)
	server.quit()
	print( "Mail Sent " )
except SMTPException:
	print( "Unable to send" )
