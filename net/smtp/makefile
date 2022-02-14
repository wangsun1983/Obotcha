smtpDir = $(netDir)/smtp/

objs += $(outtmp)/mailsender.o \
		$(outtmp)/smtpconnection.o
		
$(outtmp)/mailsender.o :$(smtpDir)/MailSender.cpp
	$(cppcompiler) $(obotchacppflags) -c $(smtpDir)/MailSender.cpp -o $(outtmp)/mailsender.o 

$(outtmp)/smtpconnection.o :$(smtpDir)/SmtpConnection.cpp
	$(cppcompiler) $(obotchacppflags) -c $(smtpDir)/SmtpConnection.cpp -o $(outtmp)/smtpconnection.o 
