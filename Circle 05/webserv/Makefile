################################################################################
#                                PROJECT'S INFO                                #
################################################################################
AUTHOR = Bassam - Mohammed - Allan

Intra_Login = Bnaji - Mpatel - Athekkep

PROJECT_NAME = webserv

DATE = 27 - 06 - 2022

################################################################################
#                                    COLORS                                    #
################################################################################
PURPLE			= \033[1;35m
BLUE			= \033[1;34m
WHITE			= \033[1;37m
LIGHT_BLUE		= \033[1;36m
GREEN			= \033[1;32m
RED				= \033[1;31m
BYELLOW			= \033[1;33m
IYELLOW			= \033[3;33m
LIGHT_GREEN		= \033[38;5;46m
GREY 			= \033[38;5;8m
ORANGE 			= \033[38;5;202m
NO_COLOR  		= \033[m
BGBLUE			= \033[46;5;1m


################################################################################
#                             DIRECTOIES STRUCTURE                             #
################################################################################

###################
# PROGRAMS' FILES #
###################
SERVER_TEST_FILES = webserv.cpp $(SERVER_NAME) $(UTILS_NAME) \
										$(REQUEST_NAME) $(RESPONSE_NAME) $(CONFIG_NAME) $(CGI_NAME)

CLIENT_TEST_FILES = $(CLIENT_NAME) $(UTILS_NAME) 

################
# SERVER FILES #
################
SERVER_FILES = Server.cpp ServerManager.cpp ServerUtils.cpp

SERVER_NAME = $(addprefix $(SERVER_DIR), ${SERVER_FILES})

SERVER_DIR = server/

##################
# RESPONSE FILES #
##################
RESPONSE_FILES = Response.cpp DirectoryListing.cpp \
									ResponseHeader.cpp ResponseUtils.cpp\
									ResponseStatusCode.cpp CGI.cpp MIME.cpp\
									ConfigConnector.cpp Container.cpp\
									CommonSetup.cpp

RESPONSE_NAME = $(addprefix $(RESPONSE_DIR), ${RESPONSE_FILES})

RESPONSE_DIR = response/

##################
# REQUEST FILES #
##################
REQUEST_FILES = Request.cpp RequestUtils.cpp

REQUEST_NAME = $(addprefix $(REQUEST_DIR), ${REQUEST_FILES})

REQUEST_DIR = request/

################
# CONFIG FILES #
################
CONFIG_FILES = Config.cpp ConfigServer.cpp Location.cpp \
								ConfigExceptions.cpp FileParser.cpp \
								Scopes.cpp MainScope.cpp NestedScope.cpp

CONFIG_NAME = $(addprefix $(CONFIG_DIR), ${CONFIG_FILES})

CONFIG_DIR = config/

###############
# UTILS FILES #
###############
UTILS_FILES = SocketManager.cpp Timer.cpp StatusCode.cpp Libft.cpp

UTILS_NAME = $(addprefix $(UTILS_DIR), ${UTILS_FILES})

UTILS_DIR = utils/

SRC_DIR = sources/

################
# CLIENT FILES #
################
CLIENT_FILES = tester.cpp

CLIENT_NAME = $(addprefix $(CLIENT_DIR), ${CLIENT_FILES})

CLIENT_DIR = client/

################
# OBJECT FILES #
################
SERVER_OBJ_NAME = $(addprefix $(OBJ_DIR), ${SERVER_TEST_FILES:%.cpp=%.o})

CLIENT_OBJ_NAME = $(addprefix $(OBJ_DIR), ${CLIENT_TEST_FILES:%.cpp=%.o})

OBJ_DIR = objs/

########
# LOGS #
########

LOG_FILE = HostToast.log

LOG_DIR = logs/


##########
# TESTER #
##########

TESTER_DIR = testers/

ifeq ($(shell uname),Darwin)
    TESTER = tester
else
    TESTER = ubuntu_tester
endif

URL = http://localhost

PORT = 8080

YOUPI_DIR = www/YoupiBanane/

CGI_TESTER = cgi-bin/cgi_tester

UBUNTU_CGI_TESTER = cgi-bin/ubuntu_cgi_tester

################################################################################
#                               COMPILATION VARS                               #
################################################################################
CXX = g++

CXX_FLAGS = -Wall -Wextra -Werror --std=c++98

# comment this if you don't want to display logs
PREPROCESSOR_MACROS = -D LOG

NAME = webserv

CLIENT = client

ifeq ($(shell uname),Darwin)
    DEFAULT_CONF = config_files/default.conf
else
    DEFAULT_CONF = config_files/default_linux.conf
endif

################################################################################
#                                    RULES                                     #
################################################################################

all: header cgi_enable $(NAME) footer

$(NAME): newlines log $(OBJ_DIR) $(SERVER_OBJ_NAME)
	@$(CXX) ${CXX_FLAGS} ${PREPROCESSOR_MACROS} $(SERVER_OBJ_NAME) -o $(NAME)
	@echo "\n\r\033[3A\033[0K\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)<webserv> Executable File Is Ready\n$(NO_COLOR)"

$(CLIENT): newlines $(OBJ_DIR) $(CLIENT_OBJ_NAME)
	@$(CXX) ${CXX_FLAGS} $(CLIENT_OBJ_NAME) -o $(CLIENT)
	@echo "\n\r\033[3A\033[0K\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)<client> Executable File Is Ready\n$(NO_COLOR)"

cgi_enable:
	@chmod +x $(CGI_TESTER)
	@chmod +x $(UBUNTU_CGI_TESTER)

newlines:
	@echo "\n\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(SERVER_DIR)
	@mkdir -p $(OBJ_DIR)/$(CONFIG_DIR)
	@mkdir -p $(OBJ_DIR)/$(RESPONSE_DIR)
	@mkdir -p $(OBJ_DIR)/$(REQUEST_DIR)
	@mkdir -p $(OBJ_DIR)/$(UTILS_DIR)
	@mkdir -p $(OBJ_DIR)/$(CLIENT_DIR)


$(OBJ_DIR)%.o : $(SRC_DIR)/*%.cpp
	@echo "\n\r\033[3A\033[0K\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)generating $@\n$(NO_COLOR)"
	@$(CXX) ${CXX_FLAGS} ${PREPROCESSOR_MACROS} -c $< -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)/$(CLIENT_DIR)%.cpp
	@echo "\n\r\033[3A\033[0K\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)generating $@\n$(NO_COLOR)"
	@$(CXX) ${CXX_FLAGS} -c $< -o $@

header: art
	@printf "\n%b" "$(NO_COLOR)"
	@echo
	@printf "\t\t$(LIGHT_GREEN)AUTHORS\t\t:\t$(WHITE)%b\n$(NO_COLOR)" "$(AUTHOR)"
	@printf "\t\t$(LIGHT_GREEN)Intra Login\t:\t$(WHITE)%b\n$(NO_COLOR)" "$(Intra_Login)"
	@printf "\t\t$(LIGHT_GREEN)NAME\t\t:\t$(WHITE)%b\n$(NO_COLOR)" "$(PROJECT_NAME)"
	@printf "\t\t$(LIGHT_GREEN)DATE\t\t:\t$(WHITE)%b\n\n$(NO_COLOR)" "$(DATE)"
	@echo "\t$(BYELLOW)LOADING...$(NO_COLOR)\n"

footer:
	@echo "$(BLUE)⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡"
	@echo "$(BLUE)⚡\t\t\t\t\t$(BYELLOW)READY\t\t\t\t\t$(PURPLE)⚡"
	@echo "$(PURPLE)⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡⚡$(NO_COLOR)"

clean_o_files:
	@rm -rf $(OBJ_DIR)
	@echo "\n\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)object files are Deleted\n$(NO_COLOR)"

clean_exec_file:
	@rm -rf $(NAME)
	@rm -rf $(CLIENT)
	@echo "\n\t$(NO_COLOR)[$(GREEN)✓$(NO_COLOR)]   $(IYELLOW)Executable file is Deleted\n$(NO_COLOR)"

clean: header clean_o_files footer

fclean: header clean_o_files clean_exec_file footer

re: header clean_o_files clean_exec_file $(NAME) footer

.PHONY: all clean fclean re

clog:
	@mkdir -p $(LOG_DIR)
	@printf "" > $(LOG_DIR)$(LOG_FILE)

log:
	@mkdir -p $(LOG_DIR)

cyoupi:
	@rm -rf $(YOUPI_DIR)
	@mkdir -p $(YOUPI_DIR)
	@echo youpi - bad extension > $(YOUPI_DIR)youpi.bad_extension
	@echo youpi - bla > $(YOUPI_DIR)youpi.bla
	@mkdir -p $(YOUPI_DIR)nop
	@mkdir -p $(YOUPI_DIR)Yeah
	@mkdir -p $(YOUPI_DIR)uploads
	@echo "|nop| youpi - bad extension" > $(YOUPI_DIR)nop/youpi.bad_extension
	@echo "|nop| other - pouic" > $(YOUPI_DIR)nop/other.pouic
	@echo "|Yeah| not happy - bad extension" > $(YOUPI_DIR)Yeah/not_happy.bad_extension

valgrind:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(NAME) $(DEFAULT_CONF)

test:
	@./$(TESTER_DIR)$(TESTER) $(URL):$(PORT)

run:
	@./$(NAME) $(DEFAULT_CONF)

run-client:
	@./$(CLIENT)

art:
	@echo "$(GREY)                            :       :.      :.      .:                               $(NO_COLOR)"
	@echo "$(GREY)                           %@*     *@%     -@@     :@@:                              $(NO_COLOR)"
	@echo "$(GREY)                          *@@.    -@@=    :@@+    .%@#                               $(NO_COLOR)"
	@echo "$(GREY)                         .@@=     %@*     #@#     =@@                                $(NO_COLOR)"
	@echo "$(GREY)                          %@#     *@%.    +@@:    :@@=                               $(NO_COLOR)"
	@echo "$(GREY)                          .@@+     #@%     +@@     -@@:                              $(NO_COLOR)"
	@echo "$(GREY)                          .@@+     #@%     +@@     -@@:                              $(NO_COLOR)"
	@echo "$(GREY)                          %@#     *@@.    +@@:    :@@=                               $(NO_COLOR)"
	@echo "$(GREY)                          @@:     #@-     *@+     -@%                                $(NO_COLOR)"
	@echo
	@echo "$(BYELLOW)                                 ..:::----:::..                                      $(NO_COLOR)"
	@echo "$(BYELLOW)                        :-+*#%@@@@@@@@@@@@@@@@@@@@%#*+=:.                            $(NO_COLOR)"
	@echo "$(BYELLOW)                   -+#@@@%#+==-:.......::.......:--=+*%@@@#+-.                       $(NO_COLOR)"
	@echo "$(BYELLOW)                =#@@%+-. .-=*#%%@@@@@@@@@@@@@@@@@%#*+-: .-+#@@%+.                    $(NO_COLOR)"
	@echo "$(BYELLOW)             :*@@*- :=*%@@%#*+=-::..        ..::-=+*#%@@%#=: :+@@#:                  $(NO_COLOR)"
	@echo "$(BYELLOW)            +@@+ :*@@@*=:                  .@@@%%#+    .-+%@@*: =@@*                 $(NO_COLOR)"
	@echo "$(BYELLOW)           +@@: *@@+:                       .:-==++        .=@@#..%@#                $(NO_COLOR)"
	@echo "$(BYELLOW)          .@@= *@%.                                           #@% :@@:               $(NO_COLOR)"
	@echo "$(BYELLOW)          .@@- #@#                                            *@@ :@@-               $(NO_COLOR)"
	@echo "$(BYELLOW)           #@% .@@#.                                        .*@@: #@%                $(NO_COLOR)"
	@echo "$(BYELLOW)            #@%: +@@#-                                    -*@@*..#@%.                $(NO_COLOR)"
	@echo "$(BYELLOW)             =@@#: =%@@                                  #@@+ .*@@+                  $(NO_COLOR)"
	@echo "$(BYELLOW)               =@@# -@@                                  %@+ +@@+.                   $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@                $(NO_COLOR)+@@.              $(BYELLOW)%@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@              $(NO_COLOR)=@@#:   =%@-        $(BYELLOW)%@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@            $(NO_COLOR)=@@#:   =%@%-         $(BYELLOW)%@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@          $(NO_COLOR)=@@#:   =@@%:           $(BYELLOW)%@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@        $(NO_COLOR)=@@%:   =%@%-   -%@-      $(BYELLOW)%@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@      $(NO_COLOR).@@#:   -%@%-   -%@%=       $(BYELLOW)%@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@       $(NO_COLOR):.   =%@%:   -%@%-         $(BYELLOW)%@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@          $(NO_COLOR)=%@%-   -%@%-           $(BYELLOW)%@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@        $(NO_COLOR).@@%:   =%@%-             $(BYELLOW)%@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@         $(NO_COLOR)-:    %@%-               $(BYELLOW)%@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@               $(NO_COLOR)::                 $(BYELLOW)%@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@                                  %@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@                                  %@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@                                  %@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@                                  %@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@                                  %@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@% -@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+ *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@%  ::::::::::::::::::::::::::::::::::::::  *@%                     $(NO_COLOR)"
	@echo "$(BYELLOW)                *@@%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%@@%                     $(NO_COLOR)"
	@echo "$(GREY)                .______________________________________________.                     $(NO_COLOR)"
