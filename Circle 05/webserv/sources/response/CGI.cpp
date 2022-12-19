/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/16 14:19:05                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/response/CGI.hpp"

CGI::CGI() : charEnv_(NULL), fdOut_(-1) {
  fdIn_[0] = -1;
  fdIn_[1] = -1;
  pathArgs_[0] = NULL;
  pathArgs_[1] = NULL;
  pathArgs_[2] = NULL;
  statusCode_ = OK;
}

CGI::CGI(Request req, std::map<STRING, STRING> cgiMap,
  const STRING CgiPath, STRING extention) :
  extention_(extention), cgiMap_(cgiMap), charEnv_(NULL),
  cgiPath_(CgiPath), req_(req), fdOut_(-1) {

  fdIn_[0] = -1;
  fdIn_[1] = -1;
  pathArgs_[0] = NULL;
  pathArgs_[1] = NULL;
  pathArgs_[2] = NULL;
  statusCode_ = OK;
}

CGI::CGI(CGI const &copy) { *this = copy; }

CGI  &CGI::operator=(CGI const &rhs) {
  if (this != &rhs) {
    fileContent_ = rhs.fileContent_;
    extention_ = rhs.extention_;
    charEnv_ = rhs.charEnv_;
    cgiMap_ = rhs.cgiMap_;
    pathArgs_[0] = rhs.pathArgs_[0];
    pathArgs_[1] = rhs.pathArgs_[1];
    pathArgs_[2] = rhs.pathArgs_[2];
    cgiPath_ = rhs.cgiPath_;
    uri_ = rhs.uri_;
    req_ = rhs.req_;
    fdIn_[0] = rhs.fdIn_[0];
    fdIn_[1] = rhs.fdIn_[1];
    body_ = rhs.body_;
    fOut_ = rhs.fOut_;
    statusCode_ = rhs.statusCode_;
  }
  return (*this);
}

CGI::~CGI() {
  if (fdOut_ > -1)
    fclose(fOut_);
  if (pathArgs_[0])
    free(pathArgs_[0]);
  if (pathArgs_[1])
    free(pathArgs_[1]);
  if (charEnv_) {
    for (size_t i = 0; i < env_.size() + 1; i++)
      delete[] charEnv_[i];
    delete[] charEnv_;
  }
}

void	CGI::setDefault(Request req, std::map<STRING, STRING> cgiMap,
  const STRING CgiPath, STRING extention) {

  req_ = req;
	cgiMap_ = cgiMap;
	cgiPath_ = CgiPath;
	extention_ = extention;
}

void    CGI::setEnvVariables(Request req) {

  if (req_.getMethod() == POST) {
    env_[CONTENT_TYPE_CGI] = req.getHeaderAt("Content-Type");
    std::ostringstream contentLength;
    contentLength << req.getBody().length();
    env_[CONTENT_LENGTH_CGI] = contentLength.str();
  }
  env_[PATH_INFO_CGI] = std::string(pathArgs_[1]);
  env_[PATH_TRANSLATED_CGI] = std::string(pathArgs_[1]);
  env_[REMOTE_ADDR_CGI] = req.getClientIP();
  env_[REQUEST_METHOD_CGI] = req.getStringMethod();
  env_[REQUEST_URI_CGI] = std::string(pathArgs_[1]);
  if (!pathArgs_[0])
    env_[SCRIPT_NAME_CGI] = "";
  else
    env_[SCRIPT_NAME_CGI] = std::string(pathArgs_[0]);
  env_[SERVER_NAME_CGI] = req.getHostName();
  env_[SERVER_PROTOCOL_CGI] = "HTTP/1.1";
  std::ostringstream port;
  port << req.getPort();
  env_[SERVER_PORT_CGI] = port.str();
  env_[SERVER_SOFTWARE_CGI] = "HostToast/1.0";
  env_[GATEWAY_INTERFACE_CGI] = std::string("CGI/1.1");
  env_[QUERY_STRING_CGI] = req.getQueryString();

  std::map<STRING, STRING> requestHeader = req.getAllHeaders();
  std::map<STRING, STRING>::iterator it = requestHeader.begin();
  for (; it != requestHeader.end(); it++) {
    STRING reqKey = it->first;
    std::transform(reqKey.begin(), reqKey.end(), reqKey.begin(), ::toupper);
    STRING key = HTTP__CGI + reqKey;
    env_[key] = it->second;
  }

  setCharEnv();
}

void    CGI::setCharEnv() {
  std::map<STRING, STRING>::iterator  it;
  size_t i = 0;

  charEnv_ = new char*[this->env_.size() + 1];
  for (it = env_.begin(); it != env_.end(); it++, i++) {
    int size = it->first.size() + it->second.size() + 2;
    STRING tmp = it->first + "=" + it->second;
    charEnv_[i] = new char[size];
    charEnv_[i] = strcpy(charEnv_[i], (const char*)tmp.c_str());
  }
	charEnv_[i] = NULL;
}

void    CGI::setFileContent() {

  if (req_.getBody().empty() && req_.getMethod() != POST)
    fileContent_ = getFileContent();
  else
    fileContent_ = req_.getBody();
}

int    CGI::initCGI() {
  char    *cwd = getcwd(NULL, 0);

  STRING  cgi_exe = getCGIExe();

  STRING  cgiPath = cwd + (CGI_PATH + cgi_exe);
  removeExtraSlash(cgiPath);
  STRING  filePath = cwd + ("/" + cgiPath_);
  removeExtraSlash(filePath);
  free(cwd);

  pathArgs_[0] = strdup(cgiPath.c_str());
  pathArgs_[1] = strdup(filePath.c_str());
  pathArgs_[2] = NULL;

  fOut_ = tmpfile();
  fdOut_ = fileno(fOut_);
  setFileContent();

  setEnvVariables(req_);

  if (pipe(fdIn_) < 0)
    return (INTERNAL_SERVER_ERROR);
  return (OK);
}

char**    CGI::getCharEnv() {
    return (charEnv_);
}

int CGI::childProcess() {
  STRING path = pathArgs_[1];

  if (chdir(path.substr(0, path.find_last_of('/')).c_str()) == -1) {
    statusCode_ = INTERNAL_SERVER_ERROR;
    exit(1);
  }
  close(fdIn_[1]);
  if(dup2(fdIn_[0], STDIN_FILENO) < 0) {
    statusCode_ = INTERNAL_SERVER_ERROR;
    exit(1);
  }
  fcntl(fdIn_[0], F_SETFD, FD_CLOEXEC);

  if (dup2(fdOut_, STDOUT_FILENO) < 0) {
    statusCode_ = INTERNAL_SERVER_ERROR;
    exit(1);
  }
  fcntl(fdOut_, F_SETFD, FD_CLOEXEC);
  close(fdIn_[0]);
  std::cout << "execve: " << getFileType(pathArgs_[0]).c_str() << std::endl;
  execve(getFileType(pathArgs_[0]).c_str(), pathArgs_, charEnv_);
  exit(1);
}

int CGI::parentProcess() {
  close(fdIn_[0]);
  if (fileContent_.length() && write(fdIn_[1],
    fileContent_.c_str(), fileContent_.length()) < 0) {
      close(fdIn_[1]);
      return INTERNAL_SERVER_ERROR;
    }
  close(fdIn_[1]);

  int status;
  if (waitpid(pid_, &status, 0) < 0)
    return (INTERNAL_SERVER_ERROR);
  if (WIFEXITED(status) && WEXITSTATUS(status) == -1)
    return (BAD_GATEWAY);
  return OK;
}

int CGI::executeCGI() {

  pid_ = fork();

  if (pid_ == -1)
    return (BAD_GATEWAY);
  else if (!pid_) {
     childProcess();
  }
  return (statusCode_);
}

STRING  CGI::readBody() {
  char buf[4096 + 1];
  int ret;

  lseek(fdOut_, 0, SEEK_SET);
  while ((ret = read(fdOut_, buf, 4096)) != 0) {
    buf[ret] = '\0';
    body_.insert(body_.length(), buf, ret);
  }
  return (body_);
}

STRING const & CGI::getBody() const {
  return (body_);
}

STRING CGI::getFileContent() {
    std::ifstream file;
    STRING        content;

    file.open(pathArgs_[1], std::fstream::in);
    if (!(file.is_open()))
        return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    content = buffer.str();
    file.close();
    return content;
}

void    CGI::removeExtraSlash(STRING &path) {

  for  (size_t it = 0; it != path.size(); it++) {
    if (path[it] == '/' && (it + 1) != path.size() && path[it + 1] == '/')
      path.erase(path.begin() + it);
  }
}

STRING    CGI::getCGIExe() {
  std::map<STRING, STRING>::iterator it = cgiMap_.begin();

  for (; it != cgiMap_.end(); it++) {
    if (extention_ == it->first)
      return (it->second);
  }
  return ("");
}

int      CGI::getReadFd() {
  return (fdOut_);
}

int     CGI::getWriteFd() {
  return (fdIn_[1]);
}

STRING  CGI::getFileType(STRING const &file) {
  MIME   mime(file);
  if (mime.getContentTypeVal() == "php")
    return ("php");
  else if (mime.getContentTypeVal() == "sh")
    return ("bash");
  return (file);
}
