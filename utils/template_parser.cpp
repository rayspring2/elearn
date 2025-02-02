#include "template_parser.hpp"

#include <map>
using namespace std;

static std::string mkdirNoErrors(const std::string& dirName) {
// do not error if dir already exists (-p flag on linux)
#ifdef _WIN32
    return ("(if not exist \"" + dirName + "\" " + SysCmd::mkdir + "\"" +
            dirName + "\")");
#else
    return (SysCmd::mkdir + "-p \"" + dirName + "\"");
#endif
}

int TemplateParser::lastParserNum = 0;
const std::string localTemplate(const int parserNum) {
    return "local" + std::to_string(parserNum) + ".html";
}

TemplateParser::TemplateParser(string _filePath) {
    filePath = _filePath;
    variableCount = 0;
    programName = to_string(TemplateParser::lastParserNum) + SysCmd::fileExtention;
    parserNum = TemplateParser::lastParserNum++;
    code = "";
    parseTemplate();
    makeExecutableTemplate();
}

string TemplateParser::getHtml(map<string, string> _context) {
    TemplateUtils::writeMapToFile(outputFolder + "/" + mapFile, &_context);
    return runGeneratedCode();
}

void TemplateParser::parseTemplate() {
    string unparsedTemplate = utils::readFile(filePath);
    int parsePointer = 0;
    while (parsePointer < (signed int)unparsedTemplate.size()) {
        int begin = findBeginOfCodeBlock(parsePointer, unparsedTemplate);
        int end = findEndOfCodeBlock(parsePointer, unparsedTemplate);
        if (begin < 0) {
            break;
        }
        appendHTMLToCode(parsePointer, begin, unparsedTemplate);
        appendCodeBlockToCode(begin, end, unparsedTemplate);
        parsePointer = end + endCodeBlockTag.size();
    }
    appendHTMLToCode(parsePointer, unparsedTemplate.size(), unparsedTemplate);
}

int TemplateParser::findBeginOfCodeBlock(int startPosition, string& unparsedTemplate) {
    size_t found = unparsedTemplate.find(beginCodeBlockTag, startPosition);
    if (found == std::string::npos) return -1;
    return found;
}

int TemplateParser::findEndOfCodeBlock(int startPosition, string& unparsedTemplate) {
    size_t found = unparsedTemplate.find(endCodeBlockTag, startPosition);
    if (found == std::string::npos) return -1;
    return found;
}

void TemplateParser::appendHTMLToCode(int begin, int end,
                                      string const& unparsedTemplate) {
    code += "\nstring __variable" + to_string(variableCount) + ";";
    code += "\n__variable" + to_string(variableCount) +
            " = __unparsedTemplate__.substr(";
    code += to_string(begin) + ", " + to_string(end - begin) + ");";
    code += "\ncout << __variable" + to_string(variableCount) + ";";
    variableCount++;
}

void TemplateParser::appendCodeBlockToCode(int begin, int end,
                                           string& unparsedTemplate) {
    if (end <= begin || begin < 0) {
        throw Server::Exception("Can not parse template " + filePath);
    }
    int codeBlockSize = end - begin - beginCodeBlockTag.size();
    code += unparsedTemplate.substr(begin + beginCodeBlockTag.size(), codeBlockSize);
}

void TemplateParser::makeExecutableTemplate() {
    generateCode();
    compileCode();
    makeLocalTemplate();
}

void TemplateParser::makeLocalTemplate() {
    string templateContent = utils::readFile(filePath);
    if (!utils::writeToFile(templateContent, outputFolder + "/" + localTemplate(parserNum))) {
        throw Server::Exception("Can not write template to local " + outputFolder + "folder");
    }
}

void TemplateParser::generateCode() {
    addReadFromTemplateToCode();
    addContextMapToCode();
    addIncludesToCode();
    addReturnToCode();
}

void TemplateParser::compileCode() {
    if (!utils::writeToFile(code, toCompileFile)) {
        throw Server::Exception("Can not write generated template code!");
    }

    string cmd = mkdirNoErrors(outputFolder) + " && " + cc + " " + toCompileFile +
                 " " + utilitiesPath + " " + strutilsPath + " -o " + outputFolder + SysCmd::slash +
                 programName + "&& " + SysCmd::rm + toCompileFile;
    string error = "Can not compile template " + filePath;
    TemplateUtils::runSystemCommand(cmd, error);
}

string TemplateParser::runGeneratedCode() {
    string cmd = SysCmd::programStart + outputFolder + SysCmd::slash +
                 programName + " " + " > " + staticTemplate;
    string error = "Error in running template  " + filePath;
    TemplateUtils::runSystemCommand(cmd, error);

    string html = utils::readFile(staticTemplate);

    cmd = SysCmd::rm + staticTemplate;
    error = "Error in deleting static template for  " + filePath;
    TemplateUtils::runSystemCommand(cmd, error);

    return html;
}

void TemplateParser::addIncludesToCode() {
    string include = "#include <iostream>\n";
    include += "#include <string>\n";
    include += "#include <map>\n";
    include += "#include <cstring>\n";
    include += "#include \"" + utilitiesHeaderPath + "\"\n";
    include += "#include \"" + strutilsHeaderPath + "\"\n";
    include += "using namespace std;\n";
    code = include + "int main(int argc, char const *argv[])\n{\n" + code + "\n";
}

void TemplateParser::addReadFromTemplateToCode() {
    code = "string __unparsedTemplate__ = utils::readFile(\"" + outputFolder + "/" +
           localTemplate(parserNum) + "\");\n" + code;
}

void TemplateParser::addReturnToCode() { code += "return 0;\n}\n"; }

void TemplateParser::addContextMapToCode() {
    string mapCode = "std::map<std::string, std::string> context;\n";
    // `mapFile` should be changed if we want to handle requests
    //  in a multi-thread non-blocking way
    mapCode += "utils::readMapFromFile(\"" + outputFolder + "/" + mapFile + "\", context);\n";
    code = mapCode + code;
}

TemplateParser::~TemplateParser() {
    deleteExecutable();
    deleteLocalTemplate();
}

void TemplateParser::deleteExecutable() {
    string cmd = SysCmd::rm + outputFolder + SysCmd::slash + programName;
    string error = "Error in deleting executable file at  " + outputFolder + "/" + programName;
    TemplateUtils::runSystemCommand(cmd, error);
}

void TemplateParser::deleteLocalTemplate() {
    string cmd = SysCmd::rm + outputFolder + SysCmd::slash + localTemplate(parserNum);
    string error = "Error in deleting local template at  " + outputFolder + "/" + localTemplate(parserNum);
    TemplateUtils::runSystemCommand(cmd, error);
}

void TemplateParser::TemplateUtils::runSystemCommand(string command, string error) {
    int ret = system(command.c_str());
#ifdef _WIN32
    if (ret != 0) {
        throw Server::Exception(error);
    }
#else
    if (WEXITSTATUS(ret) != EXIT_SUCCESS) {
        throw Server::Exception(error);
    }
#endif
}

int TemplateParser::TemplateUtils::writeMapToFile(std::string fname, std::map<std::string, std::string>* m) {
    int count = 0;
    if (m->empty()) return 0;

    FILE* fp = fopen(fname.c_str(), "w");
    if (!fp) return -errno;

    for (std::map<std::string, std::string>::iterator it = m->begin();
         it != m->end(); it++) {
        fprintf(fp, "%s=%s\n", it->first.c_str(), it->second.c_str());
        count++;
    }

    fclose(fp);
    return count;
}
