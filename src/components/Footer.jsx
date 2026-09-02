import React from 'react';

export default function Footer() {
  return (
    <footer style={{
      width: '100%',
      padding: '1.5rem',
      borderTop: '1px solid var(--border-subtle)',
      textAlign: 'center',
      color: 'var(--text-muted)',
      fontSize: '0.85rem'
    }}>
      <div style={{ maxWidth: '1200px', margin: '0 auto', display: 'flex', flexDirection: 'column', gap: '0.35rem' }}>
        <p>PocketMC Accounts — Official Global Player Identity Portal</p>
        <p style={{ fontSize: '0.75rem' }}>PocketMC is an open-source project. Not an official Minecraft product.</p>
      </div>
    </footer>
  );
}
