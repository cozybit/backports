--- a/net/bluetooth/hci_core.c
+++ b/net/bluetooth/hci_core.c
@@ -2066,16 +2066,24 @@
 	list_add(&hdev->list, &hci_dev_list);
 	write_unlock(&hci_dev_list_lock);
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	hdev->workqueue = alloc_workqueue(hdev->name, WQ_HIGHPRI | WQ_UNBOUND |
 					  WQ_MEM_RECLAIM, 1);
+#else
+	hdev->workqueue = create_singlethread_workqueue(hdev->name);
+#endif
 	if (!hdev->workqueue) {
 		error = -ENOMEM;
 		goto err;
 	}
 
+#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
 	hdev->req_workqueue = alloc_workqueue(hdev->name,
 					      WQ_HIGHPRI | WQ_UNBOUND |
 					      WQ_MEM_RECLAIM, 1);
+#else
+	hdev->req_workqueue = create_singlethread_workqueue(hdev->name);
+#endif
 	if (!hdev->req_workqueue) {
 		destroy_workqueue(hdev->workqueue);
 		error = -ENOMEM;