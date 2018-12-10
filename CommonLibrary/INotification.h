#pragma once

namespace IMFS
{
    /// <summary>
    /// Interface used for message passing between VFS implementation and Protocol handler
    /// </summary>

	enum NotificationEventType
	{
		LockAcquiredNotification,
		LockTimeoutNotification,
		FolderChangeNotification,
		CacheCleanupNotification,
		DelayedDeleteNotification
	};

	class NotificationEvent
	{
	public:
		NotificationEventType type;
		__int64 param1;
		__int64 param2;
		IManID  param3;
	};

    class INotification
    {
		public:
			/// <summary>
			/// Function that handles the notification
			/// </summary>
			/// <param name="status">Type of notification. </param>
			/// <param name="resultData">Data passed with the notification. Information specific to notification type.</param>
			/// <param name="isCancelled">Informs if this notification was a result of a cancel</param>
			/// <returns>True if notification was successfull.</returns>
			virtual bool Notification(NtStatus status, void *resultData, bool isCancelled) = 0;
    };
}
