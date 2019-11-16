import sys
import smtplib 

# creates SMTP session 
s = smtplib.SMTP('smtp.gmail.com', 587) 

# start TLS for security 
s.starttls() 

# Authentication 
s.login("lezendarysystem@gmail.com", "fuckusanskar") 

# message to be sent 
message = "fuckutanmay "

# sending the mail 
s.sendmail("lezendarysystem@gmail.com", i , message+i) 

# terminating the session 
s.quit()