import { useEffect, useState } from 'react';

import './NotificationCard.css';

type NotificationCardProps = {
    children: React.ReactNode;
    color?: string;
};

export default function NotificationCard({ children, color }: NotificationCardProps) {
    const [isVisible, setIsVisible] = useState<boolean>(true);

    useEffect(() => {
        const timeout = setTimeout(() => {
            setIsVisible(false);
        }, 2000);

        return () => clearInterval(timeout);
    }, []);

    return (
        <div
            className={`notification-card ${!isVisible ? 'fade-out' : ''}`}
            style={{
                backgroundColor: color,
            }}
        >
            {children}
        </div>
    );
}
