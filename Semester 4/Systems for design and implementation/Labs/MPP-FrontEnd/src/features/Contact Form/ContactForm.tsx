import { useRef, useState } from 'react';
import './ContactForm.css';
import { Button } from '../../shared/components/button/Button';
import { sendMail } from '../../services/Mail Service/MailService';

type ContactFormProps = {
    email: string;
};

export default function ContactForm({ email }: ContactFormProps) {
    const nameRef = useRef<HTMLInputElement>(null);
    const emailRef = useRef<HTMLInputElement>(null);
    const messageRef = useRef<HTMLTextAreaElement>(null);

    const [success, setSuccess] = useState<boolean>(false);

    const handleSubmit = () => {
        const userName = nameRef.current!.value;
        const userEmail = emailRef.current!.value;
        const message = messageRef.current!.value;

        if (userName.length == 0 || userEmail.length == 0 || message.length == 0) {
            alert('Please input contact info!');
            return;
        }

        console.log(userName, userEmail, message);

        sendMail(userName, userEmail, message, email).then(() => {
            setSuccess(true);

            setTimeout(() => {
                setSuccess(false);
            }, 3000);
        });
    };

    return (
        <div className='contact-form'>
            <div className='user-details'>
                <input type='text' className='name-input' placeholder='Your name' ref={nameRef} />
                <input type='text' className='email-input' placeholder='Email' ref={emailRef} />
            </div>

            <div className='message-box'>
                <textarea ref={messageRef} placeholder='Your message here'></textarea>
            </div>

            <Button type='button' buttonMessage='Submit' className='submit-contact' onClick={handleSubmit} />
            {success && <div className='success-message'>Mail sent successfully!</div>}
        </div>
    );
}
