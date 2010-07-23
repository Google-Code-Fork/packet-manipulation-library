#!/usr/bin/env python
import sys, smtplib, time, email
from email.MIMEMultipart import MIMEMultipart
from email.MIMEText import MIMEText

fromaddr = "scaparra.jeffrey@mail.navy.mil"
toaddrs  = ['scaparra.jeffrey@mail.navy.mil', 'kozma.michael@mail.navy.mil', 'bullock.jeff@mail.navy.mil']
scriptDirectory = "/home/scap/scripts"
configureLog=scriptDirectory+"/configure.txt"
makeLog = scriptDirectory+"/make.txt"
makeTestLog= scriptDirectory+"/makeText.txt"
testLog = scriptDirectory+"/test.txt"

winMessage = """Developers,

This is a notice that a fresh checkout of the PVAT library PacMan from
http://code.scaparra.com/PacMan was able to build and passed all test
successfully. See Attached.

Congrats,
  Tester 

DO NOT Respond to this message. This is an automated message.
"""

compileFailMessage = """Developers,
This is a notice that a fresh checkout of the PVAT library PacMan from
http://code.scaparra.com/PacMan was unable to build. See Attached.

Please Fix,
   The Compilier

DO NOT Respond to this message. This is an automated message.
"""

compileTestFailMessage = """Developers,
This is a notice that a fresh checkout of the PVAT library PacMan from
http://code.scaparra.com/PacMan was unable to build. See Attached.

Please Fix,
  The Test Compilier

DO NOT Respond to this message. This is an automated message.
"""

testFailMessage = """Developers,
This is a notice that a fresh checkout of the PVAT library PacMan from
http://code.scaparra.com/PacMan was able to build. However, the Unit Test have
failed, See Attached.

Please Fix,
  The Tester

DO NOT Respond to this message. This is an automated message.
"""

msg = MIMEMultipart()

try:
	attach1 = MIMEText( file(configureLog).read() )
	attach1.add_header('Content-Disposition', 'attachment', filename="configure.log" ) 
except IOError:
	attach1 = MIMEText( "" )
	attach1.add_header('Content-Disposition', 'attachment', filename="configure.log" ) 

try:
	attach2 = MIMEText( file(makeLog).read() )
	attach2.add_header('Content-Disposition', 'attachment', filename="make.log" ) 
except IOError:
	attach2 = MIMEText( "" )
	attach2.add_header('Content-Disposition', 'attachment', filename="make.log" ) 

try:
	attach3 = MIMEText( file(makeTestLog).read() )
	attach3.add_header('Content-Disposition', 'attachment', filename="makeTest.log" ) 
except IOError:
	attach3 = MIMEText( "" )
	attach3.add_header('Content-Disposition', 'attachment', filename="makeTest.log" ) 

try: 
	attach4 = MIMEText( file(testLog).read() )
	attach4.add_header('Content-Disposition', 'attachment', filename="test.log" ) 
except IOError:
	attach4 = MIMEText( "" )
	attach4.add_header('Content-Disposition', 'attachment', filename="test.log" ) 

try:
	type = sys.argv[1]
except IndexError:
	type = ""

if type == "win": 
	msg.attach( MIMEText( winMessage ) )
	msg['Subject'] = "PVAT Success"
elif type == "compileFail":
	msg.attach( MIMEText( compileFailMessage ) )
	msg['Subject'] = "PVAT Compilation Failing" 
elif type == "compileTestFail":
	msg.attach( MIMEText( compileTestFailMessage ) )
	msg['Subject'] = "PVAT Compilation of Tests Failing"
elif type == "testFail": 
	msg.attach( MIMEText( testFailMessage ) )
	msg['Subject'] = "PVAT Test are FAILING"
else:
	print( "useage: mail.py win|compileFail|compileTestFail|testFail" )
	sys.exit(0) 

msg.attach( attach1 )
msg.attach( attach2 )
msg.attach( attach3 )
msg.attach( attach4 )
msg['From'] = "PVAT Automated Build System <builder@KernelPanic.ncr.spawar.navy.mil>"
msg['To'] = "Developer <DEVELOPER@PVAT.SYSTEM>"
msg.preamble = "Use a better email client that accepts MIME"
	
try:
	server = smtplib.SMTP('ins.ncr.spawar.navy.mil')
	server.sendmail(fromaddr, toaddrs, msg.as_string() )
	server.quit()
	print( "Mail Sent " )
except smtplib.SMTPException:
	print( "Unable to send" )
