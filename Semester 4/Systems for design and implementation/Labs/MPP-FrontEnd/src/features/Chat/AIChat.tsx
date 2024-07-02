import { faMessage, faPaperPlane, faXmark } from '@fortawesome/free-solid-svg-icons';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { useEffect, useRef, useState } from 'react';

import './AIChat.css';
import ReactLoading from 'react-loading';
import { requestResponse } from '../../services/AI Service/AiService';

interface Message {
    text: string;
    isBot: boolean;
}

interface ChatProps {
    carId: string;
}

export default function Chat({ carId }: ChatProps) {
    const [showChat, setShowChat] = useState<boolean>(false);
    const [isAnswering, setIsAnswering] = useState<boolean>(false);

    const [messages, setMessages] = useState<Message[]>([
        {
            text: "Hi! I'm MotorMate your AI assistant ready to help you with details about this car.",
            isBot: true,
        },
    ]);

    const userInput = useRef<HTMLInputElement>(null);
    const messageDiv = useRef<HTMLDivElement>(null);

    const addMessage = (messageToAdd: Message) => {
        setMessages((messages) => [...messages, messageToAdd]);
    };

    const handleSend = () => {
        let messageText = userInput.current!.value;
        if (messageText.length == 0) return;

        userInput.current!.value = '';

        addMessage({
            text: messageText,
            isBot: false,
        });

        setIsAnswering(true);

        requestResponse(carId, messageText)
            .then((response) => {
                setIsAnswering(false);

                addMessage({
                    text: response,
                    isBot: true,
                });
            })
            .catch(() => {
                setIsAnswering(false);

                addMessage({
                    text: 'Sorry I cannot answer right now!',
                    isBot: true,
                });
            });
    };

    useEffect(() => {
        if (messageDiv.current) {
            messageDiv.current.scrollTop = messageDiv.current.scrollHeight;
        }
    }, [messages]);

    return (
        <div className='chat'>
            {showChat && (
                <div className='chat-area'>
                    <div className='close-chat'>
                        <div className='chat-title'>MotorMate</div>
                        <FontAwesomeIcon icon={faXmark} className='close-icon' onClick={() => setShowChat(false)} />
                    </div>

                    <div className='message-list' ref={messageDiv}>
                        {messages.map((message, index) => (
                            <div key={index} className={`message ${message.isBot ? 'bot-message' : 'user-message'}`}>
                                {message.text}
                            </div>
                        ))}

                        {isAnswering && <ReactLoading type='bubbles' className='loading' width={40} color='grey' />}
                    </div>

                    <div className='input-area'>
                        <input className='user-input' placeholder={'Ask MotorMate anything'} ref={userInput} />
                        <button className='send-button' disabled={isAnswering}>
                            <FontAwesomeIcon icon={faPaperPlane} onClick={handleSend} />
                        </button>
                    </div>
                </div>
            )}

            {!showChat && (
                <div className='chat-icon'>
                    <FontAwesomeIcon icon={faMessage} onClick={() => setShowChat(true)} />
                </div>
            )}
        </div>
    );
}
