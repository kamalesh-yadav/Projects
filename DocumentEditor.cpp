#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;
// abstraction for document elements
class DocumentElement{
    public:
    virtual string render()=0;
};
// concrete implimentations for text elements
class TextElement: public DocumentElement
{
    private:
    string text;
    public:
    TextElement(string text)
    {
        this->text=text;
    }
    string render() override
    {
        return text;
    }
};
// concrete implementation for image elements
class ImageElements:public DocumentElement
{
    private:
    string imagepath;
    public:
    ImageElements(string imagepath)
    {
        this->imagepath=imagepath;
    }
    string render() override
    {
        return "[Image: "+ imagepath +"]";
    }
};
// Newline element represent a line break in document
class NewlineElement:public DocumentElement
{
    public:
    string render() override
    {
        return "\n";
    }
};
// Tab space Element represent a tab space in document
class TabspaceElement:public DocumentElement
{
    public:
    string render() override
    {
        return "\t";
    }
};
// Document class responsible for holding a collection of elements
class Document
{
    private:
    vector<DocumentElement*> documentElements;
    public:
    void addElement(DocumentElement* element)
    {
        documentElements.push_back(element);
    }
    // Renders the document by concatenating the render output of all elements.
    string render()
    {
        string result;
        for(auto element:documentElements)
        {
            result+=element->render();
        }

        return result;
    }
};
// Persistance abstraction
class Persistance
{
    public:
    virtual void save(string data)=0;
};
// File storage implementation of persistance
class FileStorage:public Persistance
{
    public:
    void save(string data) override{
        ofstream outfile("document.txt");
        if(outfile)
        {
            outfile<<data;
            outfile.close();
            cout<<"Document saved to document.txt"<<endl;
        }
        else
        {
            cout<<"unable to open the file for writing"<<endl;
        }
    }
};
// PlaceHolder DB storage
class DBstorage:public Persistance
{
    public:
    void save(string data) override
    {
        // save to DB
    }
};
// Document editor class managing client interactions
class DocumentEditor
{
    private:
    Document* document;
    Persistance* storage;
    string renderedDocument;
    public:
    DocumentEditor(Document* document,Persistance* storage)
    {
        this->document=document;
        this->storage=storage;
    }
    void addText(string text)
    {
         document->addElement(new TextElement(text));
    }
     void addImage(string imagePath) {
        document->addElement(new ImageElements(imagePath));
    }

    // Adds a new line to the document.
    void addNewLine() {
        document->addElement(new NewlineElement());
    }

    // Adds a tab space to the document.
    void addTabSpace() {
        document->addElement(new TabspaceElement());
    }

    string renderDocument() {
        if(renderedDocument.empty()) {
            renderedDocument = document->render();
        }
        return renderedDocument;
    }

    void saveDocument() {
        storage->save(renderDocument());
    }


};
// client usage example
int main() {
    Document* document = new Document();
    Persistance* persistence = new FileStorage();

    DocumentEditor* editor = new DocumentEditor(document, persistence);

    // Simulate a client using the editor with common text formatting features.
    editor->addText("Hello, world!");
    editor->addNewLine();
    editor->addText("This is a real-world document editor example.");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Indented text after a tab space.");
    editor->addNewLine();
    editor->addImage("picture.jpg");

    // Render and display the final document.
    cout << editor->renderDocument() << endl;

    editor->saveDocument();

    return 0;
}