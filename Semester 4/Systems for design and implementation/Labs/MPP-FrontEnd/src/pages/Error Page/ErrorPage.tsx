import React from 'react';

import './ErrorPage.css';

type ErrorPageProps = {
    children: React.ReactNode;
};

export default function ErrorPage({ children }: ErrorPageProps) {
    return <div className='error-content'>{children}</div>;
}
