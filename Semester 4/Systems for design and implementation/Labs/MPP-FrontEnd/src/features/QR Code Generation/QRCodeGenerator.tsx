import { useRef, useState } from 'react';
import { toPng } from 'html-to-image';
import QRCode from 'react-qr-code';
import { Button } from '../../shared/components/button/Button';

import './QRCodeGenerator.css';

export default function QRCodeGenerator() {
    const details = window.location.href;

    const qrCodeRef = useRef<HTMLDivElement>(null);
    const [showQr, setShowQr] = useState<boolean>(false);

    const handleDownload = () => {
        if (qrCodeRef.current) {
            toPng(qrCodeRef.current, { cacheBust: true })
                .then((dataUrl) => {
                    const link = document.createElement('a');
                    link.download = 'qr-code.png';
                    link.href = dataUrl;
                    link.click();
                })
                .catch((err) => {
                    console.error('Could not generate image', err);
                });
        }
    };

    return (
        <>
            {!showQr && <Button type='button' buttonMessage='Generate QR' onClick={() => setShowQr(true)} />}

            {showQr && (
                <>
                    <div ref={qrCodeRef} className='qr-code-wrapper'>
                        <QRCode value={details} size={128} />
                    </div>

                    <Button type='button' buttonMessage='Download' onClick={handleDownload} />
                </>
            )}
        </>
    );
}
