/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2012 James Chen
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __UIEditBoxIMPL_H__
#define __UIEditBoxIMPL_H__

#include "ui/UIEditBox/UIEditBox.h"
#include "ui/UIEditBox/UIEditBox.h"
#include "base/CCDirector.h"
#include "2d/CCLabel.h"
#include "ui/UIHelper.h"

#define kLabelZOrder  9999

static const int CC_EDIT_BOX_PADDING_EX = 5;

namespace cocos2d {
    namespace ui{
        
        class CC_GUI_DLL EditBoxImpl
        {
        public:
            /**
             * @js NA
             */
            EditBoxImpl(EditBox* pEditBox) :
            _delegate(nullptr)
            ,_editBox(pEditBox)
            , _label(nullptr)
            , _labelPlaceHolder(nullptr)
            , _editBoxInputMode(EditBox::InputMode::SINGLE_LINE)
            , _editBoxInputFlag(EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS)
            , _keyboardReturnType(EditBox::KeyboardReturnType::DEFAULT)
            , _colText(Color3B::WHITE)
            , _colPlaceHolder(Color3B::GRAY)
            , _maxLength(-1)
            {
            };
            /**
             * @js NA
             * @lua NA
             */
            virtual ~EditBoxImpl() {}
            
            virtual bool initWithSize(const Size& size) {
                do
                {
                    
                    Rect rect = Rect(0, 0, size.width, size.height);
                    
                    this->createNativeControl(rect);
                    
                    initInactiveLabels(size);
                    setContentSize(size);
                    
                    return true;
                }while (0);
                
                return false;
            };
            
            virtual void setFont(const char* pFontName, int fontSize){
                this->setNativeFont(pFontName, fontSize * _label->getNodeToWorldAffineTransform().a);
                
                if(strlen(pFontName) > 0)
                {
                    _label->setSystemFontName(pFontName);
                }
                if(fontSize > 0)
                {
                    _label->setSystemFontSize(fontSize);
                }
            };
            
            virtual void setFontColor(const Color4B& color) {
                this->setNativeFontColor(color);
                
                _label->setTextColor(color);
            };
            
            virtual void setPlaceholderFont(const char* pFontName, int fontSize) {
                this->setNativePlaceholderFont(pFontName, fontSize * _labelPlaceHolder->getNodeToWorldAffineTransform().a);
                
                if( strlen(pFontName) > 0)
                {
                    _labelPlaceHolder->setSystemFontName(pFontName);
                }
                if(fontSize > 0)
                {
                    _labelPlaceHolder->setSystemFontSize(fontSize);
                }
            };
            
            virtual void setPlaceholderFontColor(const Color4B& color) {
                this->setNativePlaceholderFontColor(color);
                
                _labelPlaceHolder->setTextColor(color);
            };
            
            virtual void setInputMode(EditBox::InputMode inputMode) {
                _editBoxInputMode = inputMode;
                this->setNativeInputMode(inputMode);
            };
            
            virtual void setInputFlag(EditBox::InputFlag inputFlag){
                _editBoxInputFlag = inputFlag;
                this->setNativeInputFlag(inputFlag);
            };
            
            virtual void setMaxLength(int maxLength) {
                _maxLength = maxLength;
                this->setNativeMaxLength(maxLength);
            };
            
            virtual int  getMaxLength() {
                return _maxLength;
            };
            
            virtual void setReturnType(EditBox::KeyboardReturnType returnType) {
                _keyboardReturnType = returnType;
                this->setNativeReturnType(returnType);
            };
            virtual void refreshInactiveText(){
                setInactiveText(_text.c_str());
                if(_text.size() == 0)
                {
                    _label->setVisible(false);
                    _labelPlaceHolder->setVisible(true);
                }
                else
                {
                    _label->setVisible(true);
                    _labelPlaceHolder->setVisible(false);
                }
            };

            virtual void setText(const char* pText) {
                this->setNativeText(pText);
                _text = pText;
                refreshInactiveText();
            };
            
            virtual const char* getText(void){
                return _text.c_str();
            };
            
            virtual void setPlaceHolder(const char* pText) {
                if (pText != NULL)
                {
                    _placeHolder = pText;
                    if (_placeHolder.length() > 0 && _text.length() == 0)
                    {
                        _labelPlaceHolder->setVisible(true);
                    }
                    
                    _labelPlaceHolder->setString(_placeHolder);
                    this->setNativePlaceHolder(pText);
                }
            };
            
            virtual void doAnimationWhenKeyboardMove(float duration, float distance) = 0;
            
           // virtual void openKeyboard() = 0;
           // virtual void closeKeyboard() = 0;
            
            virtual void setPosition(const Vec2& pos) {};
            virtual void setVisible(bool visible) {
                this->setNativeVisible(visible);
            };
            
            virtual void setContentSize(const Size& size) {
                _contentSize = size;
                CCLOG("[Edit text] content size = (%f, %f)", size.width, size.height);
                placeInactiveLabels();
            };
            
            virtual void setAnchorPoint(const Vec2& anchorPoint) {};
            
            /**
             * check the editbox's position, update it when needed
             */
            virtual void updatePosition(float dt){};
            /**
             * @js NA
             * @lua NA
             */
            
            virtual void draw(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) {
                if(parentFlags)
                {
                    auto rect = ui::Helper::convertBoundingBoxToScreen(_editBox);
                    this->updateNativeFrame(rect);
                }
            };
            
            void setDelegate(EditBoxDelegate* pDelegate) { _delegate = pDelegate; };
            EditBoxDelegate* getDelegate() { return _delegate; };
            EditBox* getEditBox() { return _editBox; };
            
        public:
//            virtual void draw(cocos2d::Renderer *renderer, cocos2d::Mat4 const &transform, uint32_t flags) = 0;
            /**
             * @js NA
             * @lua NA
             */
            virtual void onEnter(void) {
                const char* pText = getText();
                if (pText) {
                    setInactiveText(pText);
                }
            };
            
            virtual void openKeyboard() {
                _label->setVisible(false);
                _labelPlaceHolder->setVisible(false);
                
                this->nativeOpenKeyboard();
            };
            
            virtual void closeKeyboard() {
                this->nativeCloseKeyboard();
            };
            
            
            virtual void onEndEditing(const std::string& text){
                this->setNativeVisible(false);
                
                if(text.size() == 0)
                {
                    _label->setVisible(false);
                    _labelPlaceHolder->setVisible(true);
                }
                else
                {
                    _label->setVisible(true);
                    _labelPlaceHolder->setVisible(false);
                    setInactiveText(text.c_str());
                }
            };
            
            void editBoxEditingDidBegin(){
                // LOGD("textFieldShouldBeginEditing...");
                cocos2d::ui::EditBoxDelegate *pDelegate = _editBox->getDelegate();
                
                if (pDelegate != nullptr)
                {
                    pDelegate->editBoxEditingDidBegin(_editBox);
                }
                
#if CC_ENABLE_SCRIPT_BINDING
                if (NULL != _editBox && 0 != _editBox->getScriptEditBoxHandler())
                {
                    cocos2d::CommonScriptData data(_editBox->getScriptEditBoxHandler(), "began", _editBox);
                    cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
                    cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
                }
#endif
            };
            void editBoxEditingChanged(const std::string& text){
                // LOGD("editBoxTextChanged...");
                cocos2d::ui::EditBoxDelegate *pDelegate = _editBox->getDelegate();
                _text = text;
                if (pDelegate != nullptr)
                {
                    pDelegate->editBoxTextChanged(_editBox, text);
                }
                
#if CC_ENABLE_SCRIPT_BINDING
                if (NULL != _editBox && 0 != _editBox->getScriptEditBoxHandler())
                {
                    cocos2d::CommonScriptData data(_editBox->getScriptEditBoxHandler(), "changed", _editBox);
                    cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
                    cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
                }
#endif
            };
            
            void editBoxEditingDidEnd(const std::string& text){
                // LOGD("textFieldShouldEndEditing...");
                _text = text;
                this->refreshInactiveText();
                
                cocos2d::ui::EditBoxDelegate *pDelegate = _editBox->getDelegate();
                if (pDelegate != nullptr)
                {
                    pDelegate->editBoxEditingDidEnd(_editBox);
                    pDelegate->editBoxReturn(_editBox);
                }
                
#if CC_ENABLE_SCRIPT_BINDING
                if (_editBox != nullptr && 0 != _editBox->getScriptEditBoxHandler())
                {
                    cocos2d::CommonScriptData data(_editBox->getScriptEditBoxHandler(), "ended", _editBox);
                    cocos2d::ScriptEvent event(cocos2d::kCommonEvent, (void *)&data);
                    cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
                    memset(data.eventName, 0, sizeof(data.eventName));
                    strncpy(data.eventName, "return", sizeof(data.eventName));
                    event.data = (void *)&data;
                    cocos2d::ScriptEngineManager::getInstance()->getScriptEngine()->sendEvent(&event);
                }
#endif
                
                if (_editBox != nullptr)
                {
                    this->onEndEditing(_text);
                }
            };
            
            virtual bool isEditing() = 0;
            virtual void createNativeControl(const Rect& frame) = 0;
            virtual void setNativeFont(const char* pFontName, int fontSize) = 0;
            virtual void setNativeFontColor(const Color4B& color) = 0;
            virtual void setNativePlaceholderFont(const char* pFontName, int fontSize) = 0;
            virtual void setNativePlaceholderFontColor(const Color4B& color) = 0;
            virtual void setNativeInputMode(EditBox::InputMode inputMode) = 0;
            virtual void setNativeInputFlag(EditBox::InputFlag inputFlag) = 0;
            virtual void setNativeReturnType(EditBox::KeyboardReturnType returnType) = 0;
            virtual void setNativeText(const char* pText) = 0;
            virtual void setNativePlaceHolder(const char* pText) = 0;
            virtual void setNativeVisible(bool visible) = 0;
            virtual void updateNativeFrame(const Rect& rect) = 0;
            virtual const char* getNativeDefaultFontName() = 0;
            virtual void nativeOpenKeyboard() = 0;
            virtual void nativeCloseKeyboard() = 0;
            virtual void setNativeMaxLength(int maxLength) {};
            
        protected:
            EditBoxDelegate* _delegate;
            EditBox* _editBox;
            
        private:
            void			initInactiveLabels(const Size& size){
                
                const char* pDefaultFontName = this->getNativeDefaultFontName();
                
                _label = Label::create();
                _label->setAnchorPoint(Vec2(0, 0.5f));
                _label->setColor(Color3B::WHITE);
                _label->setVisible(false);
                _editBox->addChild(_label, kLabelZOrder);
                
                _labelPlaceHolder = Label::create();
                _labelPlaceHolder->setAnchorPoint(Vec2(0, 0.5f));
//                _labelPlaceHolder->setColor(Color3B::GRAY);
                _labelPlaceHolder->setTextColor(Color4B(195, 195, 195, 255));
                _editBox->addChild(_labelPlaceHolder, kLabelZOrder);
                
                setFont(pDefaultFontName, size.height*2/3);
                setPlaceholderFont(pDefaultFontName, size.height*2/3);
            };
            
            void			setInactiveText(const char* pText){
                if(EditBox::InputFlag::PASSWORD == _editBoxInputFlag)
                {
                    std::string passwordString;
                    for(int i = 0; i < strlen(pText); ++i)
                        passwordString.append("\u25CF");
                    _label->setString(passwordString);
                }
                else
                {
                    _label->setString(pText);
                }
                // Clip the text width to fit to the text box
                float fMaxWidth = _editBox->getContentSize().width;
                float fMaxHeight = _editBox->getContentSize().height;
                Size labelSize = _label->getContentSize();
                if(labelSize.width > fMaxWidth || labelSize.height > fMaxHeight)
                {
                    _label->setDimensions(fMaxWidth, fMaxHeight);
                }
            };
            
            void            placeInactiveLabels(){
                _label->setPosition(CC_EDIT_BOX_PADDING_EX, _contentSize.height/2.0f +2);
                _labelPlaceHolder->setPosition(CC_EDIT_BOX_PADDING_EX, _contentSize.height / 2.0f);
            };
            
            Label* _label;
            Label* _labelPlaceHolder;
            EditBox::InputMode    _editBoxInputMode;
            EditBox::InputFlag    _editBoxInputFlag;
            EditBox::KeyboardReturnType  _keyboardReturnType;
            
            std::string _text;
            std::string _placeHolder;
            
            Color4B _colText;
            Color4B _colPlaceHolder;
            
            int   _maxLength;
            Size _contentSize;
        };
        
        // This method must be implemented at each subclass of EditBoxImpl.
        extern EditBoxImpl* __createSystemEditBox(EditBox* pEditBox);

    }
}

#endif /* __UIEditBoxIMPL_H__ */
